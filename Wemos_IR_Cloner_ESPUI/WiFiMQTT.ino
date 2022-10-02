//WiFi================================================================================
void wifi_init() {
  stored_ssid = preferences.getString("stored_ssid", "SSID");
  stored_pass = preferences.getString("stored_pass", "PASSWORD");
  stored_mqtt_server = preferences.getString("stored_mqtt_server", "192.168.1.10");
  stored_mqtt_topic_in = preferences.getString("stored_mqtt_topic_in", "ir/send");
  stored_mqtt_topic_out = preferences.getString("stored_mqtt_topic_out", "ir/decode");
  mqtt_enabled = preferences.getBool("mqtt_enabled", false);

  Serial.println("Connecting to : " + stored_ssid);

  WiFi.begin(stored_ssid.c_str(), stored_pass.c_str());
  uint8_t timeout = 30;
  while (timeout && WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    timeout--;
  }
  if (WiFi.status() != WL_CONNECTED) {
    wificonnected = false;
    Serial.print("\n\nHotspot creation");
    WiFi.mode(WIFI_AP);
    delay(100);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(hostname);
  } else {
    wificonnected = true;
    client.setServer(stored_mqtt_server.c_str(), 1883);
    client.setCallback(mqtt_callback);
    client.setBufferSize(2048);
  }
  dnsServer.start(DNS_PORT, "*", apIP);
  Serial.print("\nIP address : ");
  Serial.println(WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP());
}
//WiFi================================================================================

//MQTT LOOP===================================
void mqtt_loop() {
  if (wificonnected && mqtt_enabled) {
    if (!client.connected()) {
      reconnect();
      return;
    }
    client.loop();
  }
}
//MQTT LOOP===================================

//MQTT RECONNECT=============================================================
void reconnect() {
  if (millis() - last_millis > mqtt_retry_delay) {
    Serial.println("MQTT connection to : " + stored_mqtt_server);
    ESPUI.print(statusLabelId, "MQTT connection to : " + stored_mqtt_server);

    if (client.connect(hostname)) {
      Serial.println("MQTT connected !");
      ESPUI.print(statusLabelId, "MQTT connected !");

      //SUBSCRIBE to Topics--------------------------
      client.subscribe(stored_mqtt_topic_in.c_str());
      //---------------------------------------------
      
    } else {
      Serial.print("MQTT connection failed : ");
      Serial.println(client.state());
      Serial.println("Retry in 10 sec");
      ESPUI.print(statusLabelId, "MQTT connection failed !");
      last_millis = millis();
      return;
    }
  }
}
//MQTT RECONNECT=============================================================