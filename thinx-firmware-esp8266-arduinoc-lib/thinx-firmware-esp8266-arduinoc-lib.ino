#include "Arduino.h"
#include <THiNXLib.h>

THiNX thx;

/* Called after library gets connected and registered */
void finalizeCallback () {
  Serial.println("*INO: Finalize callback called.");
}

void setup() {

  Serial.begin(115200);

#ifdef __DEBUG__
  while (!Serial); // wait for debug console connection
  WiFi.begin("THiNX-IoT+", "<enter-your-ssid-password>");
#endif

   // Enter API Key and Owner ID
  thx = THiNX("71679ca646c63d234e957e37e4f4069bf4eed14afca4569a0c74abf503076732", "cedc16bb6bb06daaa3ff6d30666d91aacd6e3efbf9abbc151b4dcade59af7c12");
  thx.setFinalizeCallback(finalizeCallback);
}

/* Loop must call the thx.loop() in order to pickup MQTT messages and advance the state machine. */
void loop()
{
  thx.loop();
}
