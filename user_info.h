#ifndef STASSID
#define STASSID "HOME"
#define STAPSK  "12345678a!"
#define WRITE_API_KEY "vv12173_AP1_K3Y"
#endif

#define ONE_WIRE_BUS D3

const char* ssid     = STASSID;
const char* password = STAPSK;
//Hosts to send data
const char* host = "api.thingspeak.com";
const uint16_t port = 80;
const char* host2 = "ec2-your-ec2-address.compute.amazonaws.com";
const uint16_t port2 = 9000;
