#include <dummy.h>

/* OTA enabled firmware for Wemos D1 (ESP 8266, Arduino) */

#include "Arduino.h"
#include "FS.h"

#define __DEBUG__ // wait for serial port on boot

// 1. Include the THiNXLib
#include <THiNXLib.h>


// 2. Include your API Key from a file you don't store in repository (use .gitignore)
#include "Settings.h"

String realSize = String(ESP.getFlashChipRealSize());
String ideSize = String(ESP.getFlashChipSize());
bool flashCorrectlyConfigured = realSize.equals(ideSize);
bool fileSystemReady = false;

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


   Serial.println("* TH: Booting in 5 seconds..."); Serial.flush();

   delay(5000);

   Serial.print("* TH: SPIFFS real size = ");
   Serial.println(realSize); Serial.flush();

   Serial.print("* TH: SPIFFS IDE size = ");
   Serial.println(ideSize); Serial.flush();

   Serial.println("* TH: Checking SPIFFS:"); Serial.flush();

   if(flashCorrectlyConfigured) {
     //Serial.println("* TH: Formatting SPIFFS..."); Serial.flush();

     fileSystemReady = SPIFFS.begin();

     if (!fileSystemReady) {
       fileSystemReady = SPIFFS.format();;
       fileSystemReady = SPIFFS.begin();
     }
     Serial.println("* TH: Formatting completed. Calling SPIFFS.begin in 1sec..."); Serial.flush();
     delay(1000);
     //fileSystemReady = SPIFFS.begin();
     Serial.println("."); Serial.flush();

     if (!fileSystemReady) {
       Serial.println("*TH: Formatting SPIFFS..."); ; Serial.flush();
       SPIFFS.format();
       Serial.println("*TH: Re-mounting SPIFFS..."); ; Serial.flush();
       fileSystemReady = SPIFFS.begin();
     } else {
      Serial.println("*TH: SPIFFS mounted.");
     }
   }  else {
     Serial.println("flash incorrectly configured, SPIFFS cannot start, IDE size: " + ideSize + ", real size: " + realSize);
     return;
   }
#endif

  // 4. Initialize
  Serial.println("*TH: Initializing in 5 seconds...");

  delay(5000);

  thx = THiNX(apikey);
}

void loop()
{
  delay(10000);
  Serial.printf("Free size: %u\n", ESP.getFreeSketchSpace());


  // 5. Waits for WiFI, register, check MQTT, reconnect, update...
  //thx.loop();
}
