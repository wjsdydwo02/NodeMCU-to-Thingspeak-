# NodeMCU-to-Thingspeak

Modify the secrets.h file for this project with your network connection and ThingSpeak channel details.

function: 
 Updating temperature readings by ds18b20 to Thingspeak by NodeMCU(ESP8266) every 60 seconds. 

Requirements: 
 Requires ESP8266WiFi library, ThingSpeak library, DallasTemperature library, OneWire library. 
 Requires Wi-Fi connection
 
 ThingSpeak: https://thingspeak.com/
 OneWire: https://www.pjrc.com/teensy/td_libs_OneWire.html
 DallasTemperature: https://github.com/milesburton/Arduino-Temperature-Control-Library

Hardware:
 Using DS18b20 sensor module, NodeMCU(ESP8266)
 D3 Pin of NodeMCU is connected to signal pin of DS1b20 sensor module's signal pin
 Sensor module is powered by NodeMCU's 3V3 pin and Ground pin.
 
 
