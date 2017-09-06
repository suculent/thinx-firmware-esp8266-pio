#include "Arduino.h"
#include "FS.h"

// 1. Include the THiNXLib
#include <THiNXLib.h>

// #define __DEBUG__
#ifdef THINX_FIRMWARE_VERSION_SHORT
#ifndef THX_REVISION
#define THX_REVISION THINX_FIRMWARE_VERSION_SHORT
#endif
#else
#ifndef THX_REVISION
#define THX_REVISION String(0)
#endif
#endif

// 2. Include your API Key from a file you don't store in repository (use .gitignore)
#include "Settings.h"

// 3. Declare
THiNX thx;

bool ready = false; // SPIFFS must be ready or not used at all
bool once = false;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  delay(3000);

  Serial.setDebugOutput(true);

  Serial.print("\nTHiNXLib v");
  Serial.println(String(THX_REVISION));

#ifdef __USE_SPIFFS__
  // Equivalent of thx.fsck() method
  if (!SPIFFS.begin()) {
    Serial.println("Formatting."); Serial.flush();
    SPIFFS.format();
    if (!SPIFFS.begin()) {
      Serial.println("Failed."); Serial.flush();
      ready = false;
      return;
    } else {
      Serial.println("Formatting Succeeded."); Serial.flush();
    }
  }
#else
  ready = true;
#endif

  ready = true;

  // Force overrides WiFi before attempting to connect
  // in case we don't use EAVManager or WiFiManager

#ifdef __USE_WIFI_MANAGER__
  // WiFi Manager will do this on its own...
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAP("AP-THINX");
#else

  // Debugging station mode with configuration from Settings.h
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println("*INO: WiFi mode STA");
  WiFi.begin();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("*INO: Connected WiFi without credentials.");
  } else {
    Serial.println("*INO: Connect WiFi with build-configuration...");
    WiFi.begin(ssid, pass);
  }
  delay(2000); // wait for DHCP

#endif
}

void finalizeCallback () {
  Serial.println("*TH: Checkin finalized.");
}

void loop()
{
    if (ready) {
      if (once) {
        thx.loop();
      } else {
        once = true;
        thx = THiNX(apikey);
        thx.setFinalizeCallback(finalizeCallback);

        if (WiFi.status() == WL_CONNECTED) {
          Serial.print("*INO: Connected to ");
          Serial.println(ssid);
          Serial.print("*INO: IP address: ");
          Serial.println(WiFi.localIP());
          thx.connected = true; // force checkin
        }
      }
    }
    Serial.println(String("#")+String(millis())+String("ms"));
    delay(100);
}
