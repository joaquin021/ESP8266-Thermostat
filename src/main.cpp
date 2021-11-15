#include <Arduino.h>

#include "ThermostatData.hpp"
ThermostatData thermostatData;

#include "EventsDispatcher.hpp"
#include "MqttUtils.hpp"
#include "ShtUtils.hpp"
#include "TftUtils.hpp"
#include "ThermostatManager.hpp"
#include "WiFiUtils.hpp"

void setup() {
    Serial.begin(115200);
    Serial.println();
    pinMode(RELAY_PIN, OUTPUT);
    thermostatOff();
    refreshShtMeasures(true);
    initTft();
    connectWiFi();
    checkAndconnectToMqttServer();
}

void loop() {
    refreshShtMeasures();
    mqttClient.loop();
    detectToutch();
    checkThermostatStatus();
    checkIfWiFiStatusHasChanged();
    dispatchEvent();
    refreshMqttData();
}