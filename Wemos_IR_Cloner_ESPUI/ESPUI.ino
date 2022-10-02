//ESPUI===================================================================================================
void espui_init() {
  ESPUI.setVerbosity(Verbosity::Quiet);
  //Maintab-----------------------------------------------------------------------------------------------
  auto maintab = ESPUI.addControl(Tab, "", "Debug");
  //serialLabelId = ESPUI.addControl(Label, "CMD", "Aucune", Peterriver, maintab, textCallback);
  statusLabelId = ESPUI.addControl(Label, "IR read", "Waiting", Peterriver, maintab, textCallback);
  
  ir_cmd = ESPUI.addControl(Text, "IR CMD (Raw array)", "", Alizarin, maintab, textCallback);
  auto sendbout = ESPUI.addControl(Button, "Send", "Send", Alizarin, ir_cmd, SendCallback);
  
  ESPUI.setEnabled(sendbout, true);
  ESPUI.setEnabled(ir_cmd, true);
  //Maintab-----------------------------------------------------------------------------------------------

  //ESPUI------------------------------------------------------------------------------------------------------

  //WiFi....................................................................................
  auto wifitab = ESPUI.addControl(Tab, "", "WiFi");
  wifi_ssid_text = ESPUI.addControl(Text, "SSID", stored_ssid, Alizarin, wifitab, textCallback);
  wifi_pass_text = ESPUI.addControl(Text, "Password", stored_pass, Alizarin, wifitab, textCallback);
  ESPUI.setInputType(wifi_pass_text, "password");
  ESPUI.addControl(Max, "", "32", None, wifi_ssid_text);
  ESPUI.addControl(Max, "", "64", None, wifi_pass_text);
  mqtt_server_text = ESPUI.addControl(Text, "MQTT server", stored_mqtt_server, Alizarin, wifitab, textCallback);
  mqtt_topic_in_text = ESPUI.addControl(Text, "MQTT topic IN", stored_mqtt_topic_in, Alizarin, wifitab, textCallback);
  mqtt_topic_out_text = ESPUI.addControl(Text, "MQTT topic OUT", stored_mqtt_topic_out, Alizarin, wifitab, textCallback);
  mqtt_enabled_switch = ESPUI.addControl(Switcher, "Enable MQTT", String(mqtt_enabled), Alizarin, wifitab, textCallback);
  
  auto wifisave = ESPUI.addControl(Button, "Save", "Save", Peterriver, wifitab, SaveWifiDetailsCallback);
  auto espreset = ESPUI.addControl(Button, "", "Reboot ESP", None, wifisave, ESPReset);
  
  ESPUI.setEnabled(wifi_ssid_text, true);
  ESPUI.setEnabled(wifi_pass_text, true);
  ESPUI.setEnabled(mqtt_server_text, true);
  ESPUI.setEnabled(mqtt_topic_in_text, true);
  ESPUI.setEnabled(mqtt_topic_out_text, true);
  ESPUI.setEnabled(mqtt_enabled_switch, true);
  ESPUI.setEnabled(wifisave, true);
  ESPUI.setEnabled(espreset, true);
  //WiFi....................................................................................

  ESPUI.begin(hostname);
}
//ESPUI==================================================================================================
