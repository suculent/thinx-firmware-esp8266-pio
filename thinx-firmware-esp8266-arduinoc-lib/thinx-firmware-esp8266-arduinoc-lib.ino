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

bool spiffs_ok = false;

bool once = false;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.setDebugOutput(true);
  delay(1000);
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
  Serial.println("SPIFFS OK."); Serial.flush();
  spiffs_ok = true;
  wdt_disable();
  //once = true;
  //wdt_disable();
  //thx = THiNX(apikey); // hangs in loop
  //wdt_enable(5000);
}

void loop()
{
    if (spiffs_ok) {
      if (!once) {
        once = true;

        thx = THiNX(apikey); // hangs in loop

      } else {
        thx.loop();
      }
    }
}
