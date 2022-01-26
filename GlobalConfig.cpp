#include "/home/renzo/Arduino/rfm69gw/GlobalConfig.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>

// Default values
const char PROGMEM ENCRYPTKEY[] = "sampleEncryptKey";
const char PROGMEM MDNS_NAME[] = "rfm69gw1";
const char PROGMEM MQTT_BROKER[] = "raspi2";
const char PROGMEM RFM69AP_NAME[] = "RFM69-AP";

struct _GLOBAL_CONFIG *pGC;

uint32_t gc_checksum() {
  uint8_t *p = (uint8_t *)pGC;
  uint32_t checksum = 0;
  p += sizeof(pGC->checksum);
  for (size_t i = 0; i < (sizeof(*pGC) - 4); i++) {
    checksum += *p++;
  }
  return checksum;
}

void eeprom_setup() {
  EEPROM.begin(4096);
  pGC = (struct _GLOBAL_CONFIG *)EEPROM.getDataPtr();
  // if checksum bad init GC else use GC values
  if (gc_checksum() != pGC->checksum) {
    Serial.println("Factory reset");
    memset(pGC, 0, sizeof(*pGC));
    strcpy_P(pGC->encryptkey, ENCRYPTKEY);
    strcpy_P(pGC->rfmapname, RFM69AP_NAME);
    strcpy_P(pGC->mqttbroker, MQTT_BROKER);
    strcpy_P(pGC->mdnsname, MDNS_NAME);
    strcpy(pGC->mqttclientname, WiFi.hostname().c_str());
    pGC->networkid = NETWORKID;
    pGC->nodeid = NODEID;
    pGC->powerlevel = ((IS_RFM69HCW)?0x80:0x00) | POWER_LEVEL;
    pGC->rfmfrequency = FREQUENCY;
    pGC->checksum = gc_checksum();
    EEPROM.commit();
  }
}

void handleconfiguregwreset()
{
  pGC->checksum++;
  EEPROM.commit();
  ESP.reset();
  delay(1000);
}