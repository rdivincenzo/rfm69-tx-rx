#include <EEPROM.h>
#include <RFM69.h>  



#define NETWORKID     200  //the same on all nodes that talk to each other
#define NODEID        1

//Match frequency to the hardware version of the radio
//#define FREQUENCY     RF69_433MHZ
//#define FREQUENCY     RF69_868MHZ
//TODO: valutare il da farsi per eliminare l'include
#define FREQUENCY      RF69_915MHZ
#define IS_RFM69HCW    true // set to 'true' if you are using an RFM69HCW module
#define POWER_LEVEL    31

struct _GLOBAL_CONFIG {
  uint32_t    checksum;
  char        rfmapname[32];
  char        mqttbroker[32];
  char        mqttclientname[32];
  char        mdnsname[32];
  uint32_t    ipaddress;  // if 0, use DHCP
  uint32_t    ipnetmask;
  uint32_t    ipgateway;
  uint32_t    ipdns1;
  uint32_t    ipdns2;
  char        encryptkey[16+1];
  uint8_t     networkid;
  uint8_t     nodeid;
  uint8_t     powerlevel; // bits 0..4 power leve, bit 7 RFM69HCW 1=true
  uint8_t     rfmfrequency;
};

#define GC_POWER_LEVEL    (pGC->powerlevel & 0x1F)
#define GC_IS_RFM69HCW  ((pGC->powerlevel & 0x80) != 0)

uint32_t gc_checksum();

void eeprom_setup();

// Reset global config back to factory defaults
void handleconfiguregwreset();
