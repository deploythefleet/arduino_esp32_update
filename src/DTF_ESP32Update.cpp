#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <time.h>
#include <WiFiClientSecure.h>

#include "DTF_ESP32Update.h"
#include <stdint.h>

extern const char* isrgrootx1_cert;
extern const char* cloudflare_cert;
extern const char* deploy_the_fleet_cert;
extern const int CERT_BUNDLE_ID;

static char errstr[128];
constexpr const int NTP_MAX_WAIT_TIME_IN_SECONDS = 600; // 10 minutes

enum CertificateType {
    ISRG_ROOT_X1,
    CLOUDFLARE_ORIGIN,
    DEPLOY_THE_FLEET_X1
};

void setSystemTime()
{
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    log_i("Waiting for NTP time sync: ");

    time_t now = time(nullptr);
    while (now < NTP_MAX_WAIT_TIME_IN_SECONDS) {
        yield();
        delay(500);
        log_d(".");
        now = time(nullptr);
    }

    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);

    log_i("Current time: %s", asctime(&timeinfo));
}

void setCertificate(WiFiClientSecure& client, CertificateType certType) {
    switch (certType) {
        case ISRG_ROOT_X1:
            log_d("Setting certificate to ISRG Root X1");
            client.setCACert(isrgrootx1_cert);
            break;
        case CLOUDFLARE_ORIGIN:
            log_d("Setting certificate to Cloudflare Origin");
            client.setCACert(cloudflare_cert);
            break;
        case DEPLOY_THE_FLEET_X1:
            log_d("Setting certificate to Deploy the Fleet X1");
            client.setCACert(deploy_the_fleet_cert);
            break;
    }
}

DTF_UpdateResponse DTF_ESP32Update::getFirmwareUpdate(
    const char* updateUrl, 
    const char* currentVersion, 
    DTF_RebootOption rebootOption, 
    DTF_SetTimeOption setTimeOption
)
{
    log_i("Checking for firmware updates");

    // Append the certificate bundle ID to the update URL
    String url = String(updateUrl);
    url.reserve(strlen(updateUrl) + 12);
    if(url.indexOf("?") == -1)
    {
        url.concat("?cb=");
    }
    else
    {
        url.concat("&cb=");
    }
    url.concat(CERT_BUNDLE_ID);

    // Ensure the current time is set and accurate
    if (setTimeOption == DTF_SetTimeOption::SET_TIME)
    {
        setSystemTime();
    }

    if(rebootOption == DTF_RebootOption::NO_REBOOT)
    {
        httpUpdate.rebootOnUpdate(false);
    }

    // Create a secure client using the Let's Encrypt certificate
    WiFiClientSecure client;
    log_d("Setting certificate to ISRG Root X1");
    setCertificate(client, CertificateType::ISRG_ROOT_X1);
    client.setTimeout(20); // 20 second timeout

    // The following line invokes the update library and will send all necessary headers
    // to Deploy the Fleet for it to decision an update. Make sure the version argument
    // is always accurate as this is used to determine if a device needs an update or not.
    // Get the URL from your product dashboard in Deploy the Fleet
    t_httpUpdate_return ret = httpUpdate.update(client, updateUrl, currentVersion);
    int lastErr = client.lastError(errstr, sizeof(errstr));

    if(ret == HTTP_UPDATE_FAILED){
        log_d("Update failed. Last error: %d %s", lastErr, errstr);
        setCertificate(client, CertificateType::CLOUDFLARE_ORIGIN);
        ret = httpUpdate.update(client, updateUrl, currentVersion);

        if(ret == HTTP_UPDATE_FAILED){
            lastErr = client.lastError(errstr, sizeof(errstr));
            log_d("Update failed. Last error: %d %s", lastErr, errstr);

            // Need to change the domain to ota4.deploythefleet.io
            url.replace("ota.", "ota9.");
            log_d("Backup URL: %s", url.c_str());
            setCertificate(client, CertificateType::DEPLOY_THE_FLEET_X1);
            ret = httpUpdate.update(client, url.c_str(), currentVersion);
        }
    }

    switch (ret) {
        case HTTP_UPDATE_FAILED:
            lastErr = client.lastError(errstr, sizeof(errstr));
            log_e("Update failed. Last error: %d %s", lastErr, errstr);
            return DTF_UpdateResponse::UPDATE_FAILED;
            break;

        case HTTP_UPDATE_NO_UPDATES:
            log_i("No updates are available for this device.");
            return DTF_UpdateResponse::NO_UPDATE_AVAILABLE;
            break;

        case HTTP_UPDATE_OK:
            log_i("Update succeeded. Reboot device to apply update.");
            return DTF_UpdateResponse::UPDATE_SUCCEEDED;
            break;
        
        default:
            return DTF_UpdateResponse::NO_UPDATE_AVAILABLE;
    }
}