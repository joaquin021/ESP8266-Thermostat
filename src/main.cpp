#include <Arduino.h>

#include "ThermostatData.hpp"
ThermostatData thermostatData;

#include "MqttUtils.hpp"
#include "TftUtils.hpp"
#include "ThermostatManager.hpp"
#include "WiFiUtils.hpp"

void setup() {
    Serial.begin(115200);
    Serial.println();
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
    initTft();
    connectWiFi();
    checkAndconnectToMqttServer();
}

void loop() {
    mqttClient.loop();
    detectToutch();
    thermostat();
}