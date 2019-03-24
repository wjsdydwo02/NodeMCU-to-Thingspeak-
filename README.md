# NodeMCU-to-Thingspeak

Modify the global variables and macro parts with your network connection and ThingSpeak channel, server details.

function: 
 Updating temperature readings by ds18b20 to Thingspeak and AWS server by NodeMCU(ESP8266) every 60 seconds.
 when fails to upload on one of above servers, it will retry sending to that server for a minute.  

Requirements: 
 Requires ESP8266WiFi library,  DallasTemperature library, OneWire library. 
 Requires Wi-Fi connection
 
 OneWire: https://www.pjrc.com/teensy/td_libs_OneWire.html
 DallasTemperature: https://github.com/milesburton/Arduino-Temperature-Control-Library

Hardware:
 Using DS18b20 sensor module, NodeMCU(ESP8266)
 D3 Pin of NodeMCU is connected to signal pin of DS1b20 sensor module's signal pin
 Sensor module is powered by NodeMCU's 3V pin and Ground pin.
 
 
