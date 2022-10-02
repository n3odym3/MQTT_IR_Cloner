//Send IR from raw array======================
void SendIR(String data) {
  //Parse array-------------------------------
  Data.clear();
  deserializeJson(Data, data);
  JsonArray data_array = Data.as<JsonArray>();
  uint16_t array[data_array.size()] = {};
  for (int i = 0; i < data_array.size(); i++) {
    array[i] = (unsigned int)data_array[i];
  }
  //Parse array-------------------------------
  irsend.sendRaw(array, sizeof(array), kFrequency);
}
//Send IR from raw array======================

//Send ESPUI===========================================
void SendCallback(Control *sender, int type) {
  if (type == B_DOWN) {
    SendIR(ESPUI.getControl(ir_cmd)->value);
  }
}
//Send ESPUI===========================================

//MQTT CALLBACK===================================================
void mqtt_callback(String topic, byte *message, unsigned int length) {
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  Serial.println(messageTemp);
  SendIR(messageTemp);
}
//MQTT CALLBACK===================================================

//WiFi settings callback=====================================================
void SaveWifiDetailsCallback(Control *sender, int type) {
  if (type == B_UP) {
    stored_ssid = ESPUI.getControl(wifi_ssid_text)->value;
    stored_pass = ESPUI.getControl(wifi_pass_text)->value;
    stored_mqtt_topic_in = ESPUI.getControl(mqtt_topic_in_text)->value;
    stored_mqtt_topic_out = ESPUI.getControl(mqtt_topic_out_text)->value;
    stored_mqtt_server = String(ESPUI.getControl(mqtt_server_text)->value);
    mqtt_enabled = ESPUI.getControl(mqtt_enabled_switch)->value.toInt() ? true : false;

    preferences.putString("stored_ssid", stored_ssid);
    preferences.putString("stored_pass", stored_pass);
    preferences.putString("stored_mqtt_server", stored_mqtt_server);
    preferences.putString("stored_mqtt_topic_in", stored_mqtt_topic_in);
    preferences.putString("stored_mqtt_topic_out", stored_mqtt_topic_out);
    preferences.putBool("mqtt_enabled", mqtt_enabled);

    Serial.println(stored_ssid);
    Serial.println(stored_pass);
    Serial.println(stored_mqtt_server);
    Serial.println(stored_mqtt_topic_in);
    Serial.println(stored_mqtt_topic_out);
    Serial.println(mqtt_enabled);

    Serial.println("Saving settings to EEPROM");
  }
}
//WiFi settings callback=====================================================

//ESP Reset=================================
void ESPReset(Control *sender, int type) {
  if (type == B_UP) {
    ESP.restart();
  }
}
//ESP Reset=================================

//Default ESPUI callback======================
void textCallback(Control *sender, int type) {
}
//Default ESPUI callback======================