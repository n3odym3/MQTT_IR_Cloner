#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
IRrecv irrecv(14);
decode_results results;
IRsend irsend(4);

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <DNSServer.h>
#include "FS.h"
#include <ArduinoJson.h> //ArduinoJSON6

WiFiClient espClient;
PubSubClient client(espClient);

const IPAddress apIP(192, 168, 1, 1);
const char* apSSID = "IR_CLONER";
boolean settingMode;
String ssidList;
DNSServer dnsServer;
ESP8266WebServer webServer(80);
bool setuponce = false;


const char *ssid, *password, *mqtt_server, *mqtt_user, *mqtt_pass, *topic_READ, *topic_CMD, *HostName;
DynamicJsonDocument WIFI(2048);

void callback(String topic, byte* message, unsigned int length) {
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  irsend.sendNEC(strtoul(messageTemp.c_str(), NULL, 16));
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  irrecv.setUnknownThreshold(12);
  irsend.begin();
  irrecv.enableIRIn();

  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  if (load_wifi()) {
    if (setup_wifi()) {
      settingMode = false;
      WiFi.mode(WIFI_STA);
      client.setServer(mqtt_server, 1883);
      client.setCallback(callback);
      return;
    }
  }
  settingMode = true;
  setupMode();
}

void loop() {
  if (settingMode) {
    if(setuponce){
      setupMode();
      setuponce =false;
    }
    dnsServer.processNextRequest();
    webServer.handleClient();
  }
  else {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
  }

  if (Serial.available()) {
    String input = Serial.readString();
    Serial.println(input);
    irsend.sendNEC(strtoul(input.c_str(), NULL, 0));
  }

  if (irrecv.decode(&results)) {
    Serial.print(resultToHumanReadableBasic(&results));
    client.publish( topic_READ, resultToHumanReadableBasic(&results).c_str());
    irrecv.resume();
  }

}
