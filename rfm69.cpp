#include "rfm69.h"
#include "/home/renzo/Arduino/rfm69gw/rfm69.h"   
#include <RFM69.h>                //https://www.github.com/lowpowerlab/rfm69
#include <SPI.h>

char RadioConfig[128];

RFM69 radio;

void radio_setup(uint8_t rfmFrequency ,uint16_t nodeId, uint8_t networkId, uint8_t powerLevel,bool isRFM69HCW,const char* encryptKey) {
  int freq;
  static const char PROGMEM JSONtemplate[] =
    R"({"msgType":"config","freq":%d,"rfm69hcw":%d,"netid":%d,"power":%d})";
  char payload[128];
Serial.println("\nRadioSetup");

  radio = RFM69(RFM69_CS, RFM69_IRQ, isRFM69HCW, RFM69_IRQN);
  Serial.println("\nCustruito");
  // Hard Reset the RFM module
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, HIGH);
  delay(100);
  digitalWrite(RFM69_RST, LOW);
  delay(100);

  // Initialize radio
  Serial.println("\nPreInizialize");
  radio.initialize(rfmFrequency, nodeId, networkId);
  Serial.println("\nInizialized");
  if (isRFM69HCW) {
    Serial.println("\nPreHP");
    radio.setHighPower();    // Only for RFM69HCW & HW!
    Serial.println("\nPostHP");
  }
  Serial.println("\nPrePL");
  radio.setPowerLevel(powerLevel); // power output ranges from 0 (5dBm) to 31 (20dBm)
  Serial.println("\nPostPL");
Serial.println("\n-------------" );
Serial.println(encryptKey[0] );

  if (encryptKey[0] != '\0'){
    Serial.println("\nPreEnc");
radio.encrypt(encryptKey);
Serial.println("\nPostEnc");
  } 

  pinMode(LED, OUTPUT);
Serial.println("\n-------------");
  Serial.print("\nListening at ");
  switch (rfmFrequency) {
    case RF69_433MHZ:
      freq = 433;
      break;
    case RF69_868MHZ:
      freq = 868;
      break;
    case RF69_915MHZ:
      freq = 915;
      break;
    case RF69_315MHZ:
      freq = 315;
      break;
    default:
      freq = -1;
      break;
  }
  Serial.print(freq); Serial.print(' ');
  Serial.print(rfmFrequency); Serial.println(" MHz");

  size_t len = snprintf_P(RadioConfig, sizeof(RadioConfig), JSONtemplate,
      freq,isRFM69HCW, networkId, powerLevel);
  if (len >= sizeof(RadioConfig)) {
    Serial.println("\n\n*** RFM69 config truncated ***\n");
  }
  
}

void radio_loop(void) {
  //check if something was received (could be an interrupt from the radio)
  if (radio.receiveDone())
  {
    uint8_t senderId;
    int16_t rssi;
    uint8_t data[RF69_MAX_DATA_LEN];

    //save packet because it may be overwritten
    senderId = radio.SENDERID;
    rssi = radio.RSSI;
    memcpy(data, (void *)radio.DATA, radio.DATALEN);
    //check if sender wanted an ACK
    if (radio.ACKRequested())
    {
      radio.sendACK();
    }
    radio.receiveDone(); //put radio in RX mode
    //TODO: DA reintegrare
    //updateClients(senderId, rssi, (const char *)data);
  } else {
    radio.receiveDone(); //put radio in RX mode
  }
}
