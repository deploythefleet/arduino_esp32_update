#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <time.h>

#include "DTF_ESP32Update.h"

/**
* This is lets-encrypt-x3-cross-signed.pem
* It will be valid until 30.09.2021 (latest).
*/
const char* rootCACertificate PROGMEM = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\n" \
"MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \
"DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\n" \
"PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\n" \
"Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n" \
"AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\n" \
"rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\n" \
"OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\n" \
"xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\n" \
"7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\n" \
"aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\n" \
"HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\n" \
"SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\n" \
"ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\n" \
"AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz\n" \
"R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\n" \
"JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\n" \
"Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ\n" \
"-----END CERTIFICATE-----\n";


void setSystemTime()
{
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    #ifdef DTF_DEBUG
    Serial.print(F("Waiting for NTP time sync: "));
    #endif

    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2) {
        yield();
        delay(500);
        #ifdef DTF_DEBUG
        Serial.print(F("."));
        #endif
        now = time(nullptr);
    }

    #ifdef DTF_DEBUG
    Serial.println(F(""));
    #endif
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);

    #ifdef DTF_DEBUG
    Serial.print(F("Current time: "));
    Serial.print(asctime(&timeinfo));
    #endif
}

DTF_UpdateResponse DTF_ESP32Update::getFirmwareUpdate(const char* updateUrl, const char* currentVersion, bool setTime)
{
    #ifdef DTF_DEBUG
    Serial.println("Checking for firmware updates");
    #endif

    // Ensure the current time is set and accurate
    if (setTime)
    {
        setSystemTime();
    }

    // Create a secure client using the Let's Encrypt certificate
    WiFiClientSecure client;
    client.setCACert(rootCACertificate);
    client.setTimeout(20); // 20 second timeout

    // The following line invokes the update library and will send all necessary headers
    // to Deploy the Fleet for it to decision an update. Make sure the version argument
    // is always accurate as this is used to determine if a device needs an update or not.
    // Get the URL from your product dashboard in Deploy the Fleet
    t_httpUpdate_return ret = httpUpdate.update(client, updateUrl, currentVersion);

    switch (ret) {
        case HTTP_UPDATE_FAILED:
            #ifdef DTF_DEBUG
            Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
            #endif
            return DTF_UpdateResponse::UPDATE_FAILED;
            break;

        case HTTP_UPDATE_NO_UPDATES:
            #ifdef DTF_DEBUG
            Serial.println("No updates are available for this device.");
            #endif
            return DTF_UpdateResponse::NO_UPDATE_AVAILABLE;
            break;
    }
}