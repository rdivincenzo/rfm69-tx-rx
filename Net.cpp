#include "Net.h"
#include <ESP8266WiFi.h>

const char *ssid = "RFM69H Access Point"; // The name of the Wi-Fi network that will be created
const char *password = "Patrick1volta";   // The password required to connect to it, leave blank for an open network

void wifiAP(void) {
 
  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer
}