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

void setup() {
  Serial.begin(115200);
  //Serial.setDebugOutput(true);
  while (!Serial);

  // 4. Initialize
  Serial.println(apikey);
  thx = THiNX(apikey);
  Serial.println("*TH: Starting loop...");
}

void loop()
{
  // 5. Waits for WiFI, register, check MQTT, reconnect, update...
  thx.loop();
  Serial.printf("Free size: %u\n", ESP.getFreeSketchSpace());
  delay(10000);
}
