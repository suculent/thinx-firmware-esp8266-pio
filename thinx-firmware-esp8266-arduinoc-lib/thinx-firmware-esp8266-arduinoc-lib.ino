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
  Serial.setDebugOutput(true);

#ifdef __DEBUG__
  while (!Serial) {
      //
  };
  delay(500);
#endif

  // 4. Initialize
  Serial.println("*TH: Initializing in 5 seconds...");
  delay(5000);
  thx = THiNX(apikey);
}

void loop()
{
  delay(10000);
  // 5. Waits for WiFI, register, check MQTT, reconnect, update...  
  thx.loop();
  Serial.printf("Free size: %u\n", ESP.getFreeSketchSpace());
}
