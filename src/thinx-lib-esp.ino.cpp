# 1 "/tmp/tmpexpe49am"
#include <Arduino.h>
# 1 "/opt/workspace/src/thinx-lib-esp.ino"


#include <dummy.h>
#include "Arduino.h"

#define __DEBUG__ 


#include <THiNXLib.h>


THiNX thx;
void setup();
void loop();
#line 14 "/opt/workspace/src/thinx-lib-esp.ino"
void setup() {
  Serial.begin(115200);

#ifdef __DEBUG__
  while (!Serial);
  delay(5000);
  Serial.setDebugOutput(true);
#endif


  Serial.println("\n");
  Serial.println("*TH: Initializing in 5 seconds...");
  delay(5000);

  thx = THiNX("71679ca646c63d234e957e37e4f4069bf4eed14afca4569a0c74abf503076732", "cedc16bb6bb06daaa3ff6d30666d91aacd6e3efbf9abbc151b4dcade59af7c12");
}

void loop()
{

  thx.loop();
}