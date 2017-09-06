#include "Arduino.h"
#include "FS.h"

// #define __DEBUG__

// 1. Include the THiNXLib
#include <THiNXLib.h>

// 2. Include your API Key from a file you don't store in repository (use .gitignore)
#include "Settings.h"

// 3. Declare
THiNX thx;

bool ready = false; // SPIFFS must be ready or not used at all
bool once = false;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.setDebugOutput(true);

  wdt_disable(); // causes wdt reset if not disabled until 8 seconds
  wdt_enable(65535); // must be called from wdt_disable()

  delay(3000);
  Serial.print("THiNXLib v");
  Serial.println(VERSION);

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
  Serial.println("*THiNX: SETUP >>>");

  // Force override WiFi before attempting to connect
  // in case we don't use EAVManager or WiFiManager

#ifndef __USE_WIFI_MANAGER__
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println("*INO: WiFi mode STA");
  WiFi.begin();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("*INO: connect wifi with no saved ");
  } else {
    Serial.println("*INO: connect wifi with config value ");
    WiFi.begin(ssid, pass);
  }
  delay(2000); // wait for DHCP
#endif

}

void loop()
{
    if (ready) {
      if (once) {
        thx.loop();
      } else {
        Serial.println("*THiNX: LOOP ONE (INIT) >>>");
        once = true;
        thx = THiNX(apikey);
        if (WiFi.status() == WL_CONNECTED) {
          Serial.print("*INO: Connected to ");
          Serial.println(ssid);
          Serial.print("*INO: IP address: ");
          Serial.println(WiFi.localIP());
          thx.connected = true; // force checkin
        }
      }
    }
    Serial.println(millis());
    delay(100);
}
