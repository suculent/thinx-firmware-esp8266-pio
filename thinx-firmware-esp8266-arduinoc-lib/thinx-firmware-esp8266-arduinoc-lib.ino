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

/*
#ifndef __USE_WIFI_MANAGER__
  // Force-override WiFi before attempting to connect in case we don't use EAVManager
  // or WiFiManager with configuration from Settings.h
  ETS_UART_INTR_DISABLE();
  WiFi.disconnect();
  ETS_UART_INTR_ENABLE();
  WiFi.mode(WIFI_STA);
  Serial.println("*INO: WiFi mode STA");
  //WiFi.begin();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("*INO: Connected WiFi using saved credentials.");
  } else {
    Serial.println("*INO: Connect WiFi with build-configuration...");
    WiFi.begin("THiNX-IoT+", "<enter-your-ssid-password>");
    delay(2000); // wait for DHCP, otherwise falls to AP mode
  }
#endif
*/

  ETS_GPIO_INTR_DISABLE();
  thx = THiNX("71679ca646c63d234e957e37e4f4069bf4eed14afca4569a0c74abf503076732"); // API Key
  first_loop = false;
  ETS_GPIO_INTR_ENABLE();

}

// ICACHE_RAM_ATTR ?
void finalizeCallback () {
  Serial.println("*TH: Finalize callback called.");
}

unsigned long frame_counter = 0;

void loop()
{
  if (first_loop) {
    // thx = THiNX("71679ca646c63d234e957e37e4f4069bf4eed14afca4569a0c74abf503076732"); // API Key
    first_loop = false;
    Serial.println(" ");
    Serial.println("» THiNX successfully initialized.");
    Serial.println(" ");
  } else {
    thx.loop();

    // Prints millis every 100.000th frame, resets counter
    /*
    frame_counter++;
    if (frame_counter % 10000 == 0) {
      Serial.println(millis());
      frame_counter = 0;
    } else {
      delay(1);
    } crash? */
  }
  delay(1);
}
