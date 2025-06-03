#include <DTF_ESP32Update.h>
#include <WiFi.h>

// You must uncomment the following 4 lines and set each one to appropriate values for your project

// #define WIFI_SSID       "" // The name of your WiFi network
// #define WIFI_PASSWORD   "" // Your WiFi network password
// #define DTF_PRODUCT_ID  "" // Your product id from the Deploy the Fleet settings
// String CURRENT_VERSION = ""; // The version of this firmware to be sent to Deploy the Fleet for update decisioning

#ifndef WIFI_SSID
#error You must define WIFI_SSID and WIFI_PASSWORD
#endif

#ifndef DTF_PRODUCT_ID
#error You must provide your Deploy the Fleet product ID in the DTF_PRODUCT_ID define at the top of the file
#endif

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

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
}

void loop() {
  // This static variable ensures that the loop function will only check for updates
  // a single time after boot.
  static bool checkedForUpdates = false;

  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
      if (!checkedForUpdates)
      {
        checkedForUpdates = true; // don't check for updates again
        auto response = DTF_ESP32Update::getFirmwareUpdate(DTF_PRODUCT_ID, CURRENT_VERSION.c_str(), DTF_ESP32Update::RebootOption::NO_REBOOT);
        
        Serial.print("DTF Response: ");
        Serial.println((int)response);
      }
    Serial.println("This is version " + CURRENT_VERSION);
    delay(5000);
  }
}