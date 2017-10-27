#include "Arduino.h"

// 1. Include the THiNXLib
#include <THiNXLib.h>

// #define __DEBUG__

// 3. Declare
THiNX thx;

bool first_loop = true;

void setup() {
  Serial.begin(115200);
#ifdef __DEBUG__
  while (!Serial); // wait for debug console connection; may block without Serial!
  Serial.setDebugOutput(false);
  delay(3000);
#endif

#ifndef __USE_WIFI_MANAGER__
  Serial.println(F("*INO: Connecting to WiFi using hardcoded configuration..."));
  WiFi.disconnect();
  WiFi.begin("THiNX-IoT+", "<enter-your-ssid-password>"); // enter your WiFi credentials here if those are not pre-build as THINX_ENV_SSID and THINX_ENV_PASS
  delay(2000);
#endif

  thx = THiNX("71679ca646c63d234e957e37e4f4069bf4eed14afca4569a0c74abf503076732"); // API Key
  first_loop = false;
}

/* ICACHE_RAM_ATTR */ void finalizeCallback () {
  Serial.println("*TH: Finalize callback called.");
}

unsigned long frame_counter = 0;

void loop()
{
  if (first_loop) {
    first_loop = false;
    Serial.println(" ");
    Serial.println("» THiNX successfully initialized.");
    Serial.println(" ");
  } else {
    thx.loop();
  }
  delay(1);
}
