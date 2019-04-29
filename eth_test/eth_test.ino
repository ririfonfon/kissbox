
#include <Ethernet2.h>

#define DEBUG 1         // Comment to disable Serial


//
// WIFI
//
const char* ssid = "stratum";
const char* password = "9000leds";
const bool useWIFI = false;

//
// NETWORK
//
IPAddress server(192, 168, 0, 255);
unsigned int udpPort_me = 3738;  // Node port to listen on
unsigned int udpPort_remote = 3737;  // Server port to speak to

char nodeName[30];

const int MTUu = 1472;  // Usable MTU (1500 - 20 IP - 8 UDP)
unsigned char incomingPacket[MTUu];  // buffer for incoming packets

const int INFO_TIME = 500;
unsigned long lastUpdate = 0;

void setup()
{
  // NAME
  sprintf(nodeName, "Hnode");

  // SERIAL
#ifdef DEBUG
  Serial.begin(115200);
  delay(100);
  Serial.println("\nHello!\n");
  Serial.println(nodeName);
#endif

  // UDP SOCKET START
  eth_start();
}


void loop()
{
  // Check if DATA received
  bool new_data;
  new_data =  eth_read(incomingPacket);
  yield();

  // New DATA received: set LEDS
  if ( new_data ) {
    // The UDP message is stored in "incomingPacket"
  }

  // Inform + HeartBeat
  if (millis() - lastUpdate > INFO_TIME) {

    // send INFO
    eth_send( nodeName );

    lastUpdate = millis();

#if defined(DEBUG_MSG)
    Serial.printf("INFO packet sent: %s\n", nodeName);
#endif
  }
  yield();
}
