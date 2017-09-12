#include "Arduino.h"
#include "FS.h"

// 1. Include the THiNXLib
#include <THiNXLib.h>

// #define __DEBUG__

// 3. Declare
THiNX thx;

bool once = false;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.setDebugOutput(true);

#ifdef __USE_SPIFFS__
  // Equivalent of thx.fsck() method
  if (!SPIFFS.begin()) {
    Serial.println("Formatting."); Serial.flush();
    SPIFFS.format();
    if (!SPIFFS.begin()) {
      Serial.println("Failed."); Serial.flush();
      return;
    } else {
      Serial.println("Formatting Succeeded."); Serial.flush();
    }
  }
#endif

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
}

// ICACHE_RAM_ATTR ?
void finalizeCallback () {
  Serial.println("*TH: Finalize callback called.");
}

unsigned long frame_counter = 0;

void loop()
{
  //Serial.print("*INO: "); Serial.print(millis()); Serial.println(" > "); Serial.flush();
  if (once == true) {
    thx.loop();
    frame_counter++;
    // millis every 100th frame
    if (frame_counter % 100000 == 0) {
      Serial.println(millis());
      frame_counter = 0;
    }
  } else {
    thx = THiNX("71679ca646c63d234e957e37e4f4069bf4eed14afca4569a0c74abf503076732"); // API Key
    once = true;
  }
  delay(10);
}
