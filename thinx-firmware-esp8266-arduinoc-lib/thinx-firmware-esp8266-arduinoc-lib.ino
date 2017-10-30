#include "Arduino.h"

// 1. Include the THiNXLib
#include <THiNXLib.h>

// 2. Find 'thinx.h' in THiNXLib and enter your THINX_OWNER identifier
// from RTM Console > User Profile > Overview

// 3. Declare
THiNX thx;

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

  thx = THiNX("71679ca646c63d234e957e37e4f4069bf4eed14afca4569a0c74abf503076732", "cedc16bb6bb06daaa3ff6d30666d91aacd6e3efbf9abbc151b4dcade59af7c12"); // Enter API Key and Owner ID
  thx.setFinalizeCallback(finalizeCallback); // called after library gets connected and registered
}

void loop()
{
  thx.loop();
}
