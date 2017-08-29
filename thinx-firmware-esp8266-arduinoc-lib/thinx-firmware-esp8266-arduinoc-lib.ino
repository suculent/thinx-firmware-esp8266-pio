/* OTA enabled firmware for Wemos D1 (ESP 8266, Arduino) */

#include <dummy.h>
#include "Arduino.h"

#define __DEBUG__ // wait for serial port on boot

// 1. Include the THiNXLib
#include <THiNXLib.h>

// 2. Include your API Key from a file you don't store in repository (use .gitignore)
#include "Settings.h"

// OR Enter your API Key if not using in Settings.h
// String apikey = "71679ca646c63d234e957e37e4f4069bf4eed14afca4569a0c74abf503076732";

// 3. Declare
THiNX thx;

void setup() {
  Serial.begin(115200);
#ifdef __DEBUG__
  while (!Serial);
  delay(500);
  Serial.setDebugOutput(true);
#endif

  // 4. Initialize
  Serial.println("*TH: Initializing...");
  thx = THiNX(apikey);
}

void loop()
{
  delay(10000);
  // 5. Waits for WiFI, register, check MQTT, reconnect, update...
  thx.loop();
  Serial.printf("Free size: %u\n", ESP.getFreeSketchSpace());
}
