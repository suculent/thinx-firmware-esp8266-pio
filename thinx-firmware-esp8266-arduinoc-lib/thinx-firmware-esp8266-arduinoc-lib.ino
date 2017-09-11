#include "Arduino.h"
#include "FS.h"

// 1. Include the THiNXLib
#include <THiNXLib.h>

// #define __DEBUG__

// 2. Include your API Key from a file you don't store in repository (use .gitignore)
#include "Settings.h"

// 3. Declare
THiNX thx;

bool once = false;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  delay(3000);

  Serial.setDebugOutput(true);

#ifdef __USE_SPIFFS__
  // Equivalent of thx.fsck() method
  if (!SPIFFS.begin()) {
    Serial.println("Formatting."); Serial.flush();
    SPIFFS.format();
    if (!SPIFFS.begin()) {
      Serial.println("Failed."); Serial.flush();
      return;
    } else {
      Serial.println("Formatting Succeeded."); Serial.flush();
    }
  }
#endif

#ifndef __USE_WIFI_MANAGER__
  // Force-override WiFi before attempting to connect in case we don't use EAVManager
  // or WiFiManager with configuration from Settings.h
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  Serial.println("*INO: WiFi mode STA");
  WiFi.begin();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("*INO: Connected WiFi using saved credentials.");
    thx.connected = true;
  } else {
    Serial.println("*INO: Connect WiFi with build-configuration...");
    WiFi.begin(ssid, pass);
  }
#endif

  thx = THiNX(apikey); // will not start connecting before loop() called
  delay(3000); // wait for DHCP, otherwise falls to AP mode
}

ICACHE_RAM_ATTR void finalizeCallback () {
  Serial.println("*TH: Finalize callback called.");
}

unsigned long frame_counter = 0;

void loop()
{
  Serial.println("*INO: > ");

  if (once == true) {

    Serial.println("*INO: LOOP > ");
    thx.loop();
    //Serial.println("*INO: LOOP < ");

    frame_counter++;

    // millis every 100th frame
    if (frame_counter % 100000 == 0) {
      Serial.println(millis());
      frame_counter = 0;
    }

  } else {

    Serial.println("*INO: ONCE > ");

    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("*INO: Connected to ");
      Serial.println(ssid);
      Serial.print("*INO: IP address: ");
      Serial.println(WiFi.localIP());
    } else {
      if (WiFi.getMode() == WIFI_STA) {
        Serial.println("*INO: WIFI_STA on first loop...");
      }
      if (WiFi.getMode() == WIFI_AP) {
        Serial.println("*INO: WIFI_AP on first loop...");
      }
    }

    thx = THiNX(apikey);
    once = true;
    thx.setFinalizeCallback(finalizeCallback);
    Serial.println("*INO: ONCE < ");
  }

  //Serial.println(millis()); Serial.flush();
  //delay(1);
}
