# IR Cloner

<img src="https://github.com/n3odym3/MQTT_IR_Cloner/blob/master/Img/Module.JPG" width="60%">

This module allows to decode and replicate IR remotes while being remotely controllable by MQTT.

## ESPUI

At the first boot or if the WiFi is unavailable, the ESP will create an accespoint named **IR-CLONER**.

Connect to this AP using your smartphone or computer and go to **http://192.168.4.1**

<img src="https://github.com/n3odym3/MQTT_IR_Cloner/blob/master/Img/WiFiSettings.PNG" width="60%"> 

The WiFI and MQTT are not mandatory, the device can be used with the AP and ESPUI interface 

<img src="https://github.com/n3odym3/MQTT_IR_Cloner/blob/master/Img/IRControl.PNG" width="60%"> 

## Control

When a remote control is detected the raw sequence is decoded and can be retrieved from : 
- Serial port : baud rate = 115200 by default
- ESPUI interface : Debug tab and IR CMD pannel
- MQTT : MQTT Topic out

You can send an IR command using :
- Serial port : paste the raw sequence array
- ESPUI interface : paste the raw sequence array, press ENTER and clic on the **SEND** button
- MQTT : MQTT Topic in

## Supplies
- Wemos D1
- IR LED
- IR Receiver
- 2N2222 Transistor
- 100Ohm and 4.7kOhm resitors
- 2x 10x3mm neodymium magnets

## Wiring
<img src="https://github.com/n3odym3/MQTT_IR_Cloner/blob/master/Img/Diagram.PNG" width="20%"> 

- Emmiter : GND
- Base : D2 (GPIO 4)
- Collector : LED (-) 
- IR Receiver : D5 (GPIO 14) 

## Dependencies 
- [ESPAsyncWebserver](https://github.com/me-no-dev/ESPAsyncWebServer)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
- [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)
- [ESPUI](https://github.com/s00500/ESPUI)
- [PubSubClient.h](https://github.com/knolleary/pubsubclient)
- [Preferences](https://github.com/vshymanskyy/Preferences)

