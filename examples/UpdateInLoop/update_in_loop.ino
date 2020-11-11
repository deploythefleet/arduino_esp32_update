#include <DTF_ESP32Update.h>
#include <WiFi.h>
#include <WiFiMulti.h>

// You must uncomment the following 4 lines and set each one to appropriate values for your project

// #define WIFI_SSID       "" // The name of your WiFi network
// #define WIFI_PASSWORD   "" // Your WiFi network password
// #define DTF_UPDATE_URL  "" // Your product update url from the Deploy the Fleet dashboard
// String CURRENT_VERSION = ""; // The version of this firmware to be sent to Deploy the Fleet for update decisioning

#ifndef WIFI_SSID
#error You must define WIFI_SSID and WIFI_PASSWORD
#endif

#ifndef DTF_UPDATE_URL
#error You must provide your Deploy the Fleet update url in the DTF_UPDATE_URL define at the top of the file
#endif

WiFiMulti WiFiMulti;

void setup() {
  // put your setup code here, to run once:
    // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println("Deploy the Fleet ESP32 Update Example");

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
  // This static variable ensures that the loop function will only check for updates
  // a single time after boot.
  static bool checkedForUpdates = false;

  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
      if (!checkedForUpdates)
      {
        checkedForUpdates = true; // don't check for updates again
        DTF_ESP32Update::getFirmwareUpdate(DTF_UPDATE_URL, CURRENT_VERSION.c_str());
      }
    Serial.println("This is version " + CURRENT_VERSION);
    delay(5000);
  }
}