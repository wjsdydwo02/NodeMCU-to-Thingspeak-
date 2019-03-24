#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#ifndef STASSID
#define STASSID "HOME"
#define STAPSK  "12345678a!"
#define WRITE_API_KEY "4GLHFIU5OI4KALEQ"
#endif

#define ONE_WIRE_BUS D3

const char* ssid     = STASSID;
const char* password = STAPSK;
//Hosts to send data
const char* host = "api.thingspeak.com";
const uint16_t port = 80;
const char* host2 = "ec2-52-79-239-180.ap-northeast-2.compute.amazonaws.com";
const uint16_t port2 = 9000;


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  sensors.begin();
  delay(750);
}

int failed = 0;
unsigned long timer = millis();
void loop() {

  float temp = - 127.0;  

  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);

  // Use WiFiClient class to create TCP connections to Thingspeak.com
  WiFiClient client;
  if(failed ==  0){
    Serial.print("connecting to ");
    Serial.print(host);
    Serial.print(':');
    Serial.println(port);
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      Serial.println("wait 5 sec...");
      delay(5000);
      failed = 0;
      if(millis()-timer>60000)
        failed = 1;
      return;
    }

  // This will send the request to Thingspeak.com
    String req = "GET /update?api_key=" + String(WRITE_API_KEY) + "&field1=" + String(temp) + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n";
  
  client.print(req);


  Serial.println("closing connection");
  client.stop();
  failed = 1;
  }

  if (failed == 1){
    Serial.print("connecting to ");
    Serial.print(host2);
    Serial.print(':');
    Serial.println(port2);
    if (!client.connect(host2, port2)) {
      Serial.println("connection failed");
      Serial.println("wait 5 sec...");
      delay(5000);
      failed = 1;
      if(millis()-timer>60000)
        failed = 0;
      return;
    }

    // This will send the request to AWS server
    String req = "GET /update?value=" + String(temp) + " HTTP/1.1\r\n" +
                 "Host: " + host2 + "\r\n" +
                 "Connection: close\r\n\r\n";
  
    client.print(req);


    Serial.println("closing connection");
    client.stop();
    failed = 0;
  }
  timer = millis() - timer;
  if(60000>timer)
    delay(60000-timer); // Wait to update the channel with 60 sec interval
  timer = millis();


}
