#include "Arduino.h"
#include "FS.h"

// 1. Include the THiNXLib
#include <THiNXLib.h>

// #define __DEBUG__

// 2. Include your API Key from a file you don't store in repository (use .gitignore)
#include "Settings.h"

// 3. Declare
THiNX thx;

bool once = false;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  delay(3000);

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

  // Force overrides WiFi before attempting to connect
  // in case we don't use EAVManager or WiFiManager

#ifdef __USE_WIFI_MANAGER__

  //WiFi Manager will start AP if it fails to connect:
  ETS_UART_INTR_DISABLE();
  WiFi.disconnect();
  ETS_UART_INTR_ENABLE();
  // WiFi.mode(WIFI_AP);
  // WiFi.softAP("AP-THINX");

#else

  // Debugging station mode with configuration from Settings.h
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println("*INO: WiFi mode STA");
  WiFi.begin();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("*INO: Connected WiFi without credentials.");
  } else {
    Serial.println("*INO: Connect WiFi with build-configuration...");
    WiFi.begin(ssid, pass);
  }
  delay(2000); // wait for DHCP

#endif
}

void finalizeCallback () {
  Serial.println("*TH: Checkin finalized.");
}

void loop()
{
    if (once) {
      thx.loop();
    } else {
      once = true;
      thx = THiNX(apikey);
      thx.setFinalizeCallback(finalizeCallback);

      if (WiFi.status() == WL_CONNECTED) {
        Serial.print("*INO: Connected to ");
        Serial.println(ssid);
        Serial.print("*INO: IP address: ");
        Serial.println(WiFi.localIP());
        thx.connected = true; // force checkin
      }
    }
    //Serial.println(String("#")+String(millis())+String("ms")); Serial.flush();
    delay(100);
}
