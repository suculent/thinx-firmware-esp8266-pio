#include "Arduino.h"

// 1. Include the THiNXLib
#include <THiNXLib.h>

// 2. Find 'thinx.h' in THiNXLib and enter your THINX_OWNER identifier
// from RTM Console > User Profile > Overview

// 3. Declare
THiNX thx;

bool first_loop = true;

/* ICACHE_RAM_ATTR */ void finalizeCallback () {
  Serial.println("*INO: Finalize callback called.");
}

void setup() {
  Serial.begin(115200);
#ifdef __DEBUG__
  while (!Serial); // wait for debug console connection; may block without Serial!
  Serial.setDebugOutput(false);
  delay(3000);
#endif

  thx = THiNX("71679ca646c63d234e957e37e4f4069bf4eed14afca4569a0c74abf503076732"); // Enter API Key
  thx.setFinalizeCallback(finalizeCallback); // called after library gets connected and registered
  first_loop = false;
}

unsigned long frame_counter = 0;

void loop()
{
  thx.loop();
}
