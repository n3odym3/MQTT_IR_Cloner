//Web server=======================
#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined ESP32
#include <WiFi.h>
#define LED_BUILTIN 2
#else
#error Architecture unrecognized by this code.
#endif

#include <Preferences.h>
Preferences preferences;
#include <DNSServer.h>
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
const char* hostname = "IR-CLONER";
bool wificonnected = false;
//Web server=======================

//MQTT=============================
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);
int mqtt_retry_delay = 10000;
unsigned long last_millis = 0;
//MQTT=============================

//ESPUI=================================================================================================================
#include <ESPUI.h>
uint16_t wifi_ssid_text, wifi_pass_text, mqtt_server_text, mqtt_topic_in_text, mqtt_topic_out_text, mqtt_enabled_switch;
uint16_t statusLabelId, serialLabelId, ir_cmd;
String option;
String stored_ssid, stored_pass, stored_mqtt_server, stored_mqtt_topic_in, stored_mqtt_topic_out;
bool mqtt_enabled = false;
//ESPUI=================================================================================================================

//ArduinoJSON=====================
#include <ArduinoJson.h>
DynamicJsonDocument Data(2048);
//ArduinoJSON=====================

//IR==============================
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
IRrecv irrecv(14);
decode_results results;
IRsend irsend(4);
const uint16_t kFrequency = 38000;
//IR==============================

//SETUP===========================
void setup() {
  Serial.begin(115200);
  Serial.println();

  //IR----------------------------
  irrecv.setUnknownThreshold(12);
  irsend.begin();
  irrecv.enableIRIn();
  //IR----------------------------

  //WiFi-------------------------
  preferences.begin("Settings");
  wifi_init();
  espui_init();
  //WiFi-------------------------
}
//SETUP===========================

//LOOP===============================================================
void loop() {
  dnsServer.processNextRequest();

  //Serial CMD-----------------------------------
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    SendIR(input);
  }
  //Serial CMD-----------------------------------

  if (irrecv.decode(&results)) {
    //Parse array----------------------------------
    Data.clear();
    JsonArray data_array = Data.to<JsonArray>();
    String array_out = "";
    for (uint16_t i = 1; i < results.rawlen; i++) {
      data_array.add(results.rawbuf[i] * RAWTICK);
    }
    serializeJson(data_array, array_out);
    //Parse array----------------------------------

    //Print array---------------------------------------------------
    Serial.println(array_out);
    ESPUI.print(statusLabelId, array_out);
    client.publish(stored_mqtt_topic_out.c_str(), array_out.c_str());
    //Print array---------------------------------------------------

    irrecv.resume();
  }

  mqtt_loop();
}
//LOOP===============================================================
