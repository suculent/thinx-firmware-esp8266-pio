#include <dummy.h>

/* OTA enabled firmware for Wemos D1 (ESP 8266, Arduino) */

#include "Arduino.h"
#include "FS.h"

#define __DEBUG__ // wait for serial port on boot

// 1. Include the THiNXLib
#include <THiNXLib.h>

// 2. Include your API Key from a file you don't store in repository (use .gitignore)
#include "Settings.h"

// 3. Declare
THiNX thx;

bool ready = false; // THiNX will not work unless SPIFFS is ready
bool once = false;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.setDebugOutput(true);

  wdt_disable();
  delay(3000);

#ifdef __USE_SPIFFS_
  // Equivalent of FSCK method, must happen before WiFi is enabled
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
#endif

  ready = true;
  Serial.println("*THiNX: SETUP >>>");

  // Force override WiFi before attempting to connect

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

  Serial.print("*INO: Connected to ");
  Serial.println(ssid);
  delay(2000); // wait for DHCP
  Serial.print("*INO: IP address: ");
  Serial.println(WiFi.localIP());

  Serial.setDebugOutput(true);

}

unsigned long loop_counter = 0;

void loop()
{
    loop_counter++;
    if (ready) {
      if (once) {
        // Serial.println("*THiNX: LOOP >>>");
        thx.loop();
      } else {
        once = true;
        Serial.println("*THiNX: LOOP ONE (INIT) >>>");
        thx = THiNX(apikey); // hangs in loop
        if (WiFi.status() == WL_CONNECTED) {
          thx.connected = true; // force checkin
        }
      }
    }
    Serial.println(millis());
    delay(100);
}
