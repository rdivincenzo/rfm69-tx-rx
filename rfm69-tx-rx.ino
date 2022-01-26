
#include "rfm69.h"
#include "Net.h"
#include "WebServer.h"
#include "Websocket.h"
#include <pgmspace.h>

const char ENCRYPTKEY[] = "sampleEncryptKey";

void setup() {
  Serial.begin(9600);
  Serial.println("\nRFM69 WiFi Gateway");

  // Serial.println(ESP.getResetReason());

  // Adafruit Huzzah has an LED on GPIO0 with negative logic.
  // Turn if off.
  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);

  // eeprom_setup();
  wifiAP();
  webServerSetup();
  startWebSocket();
  radio_setup(86, 1, 200, true, 30, ENCRYPTKEY);
}

void loop() {
  webServerLoop();
  webSocketLoop();
  radio_loop();
}