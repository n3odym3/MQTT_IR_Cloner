# IR Cloner

<img src="https://github.com/n3odym3/MQTT_IR_Cloner/blob/master/Img/Module.JPG" width="80%">

This module allows to decode and replicate IR remotes while being remotely controllable by MQTT.

## Supplies
- Wemos D1
- IR LED
- IR Receiver
- 2N2222 Transistor
- 100Ohm and 4.7kOhm resitors
- 2x 10x3mm neodymium magnets

## Wiring
<img src="https://github.com/n3odym3/MQTT_IR_Cloner/blob/master/Img/Diagram.PNG" width="40%"> 

- Emmiter : GND
- Base : D2 (GPIO 4)
- Collector : LED (-) 
- IR Receiver : D5 (GPIO 14) 

## Control

When a remote control is detected the sequence is sent in Hexadecimal format (+ size and protocol) via MQTT on the "Read" topic. Commands can be retransmitted by sending a Hexadecimal string on the "CMD" topic.

## Dependencies 
- [ESP8266 SPIFFS upload tool!](https://github.com/esp8266/arduino-esp8266fs-plugin)
- IRremoteESP8266.h
- PubSubClient.h
- ArduinoJson.h
