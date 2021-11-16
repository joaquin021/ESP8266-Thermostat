#include <Arduino.h>
#include <ESP8266mDNS.h>

#include "ThermostatData.hpp"
ThermostatData thermostatData;

#include "EventsDispatcher.hpp"
#include "MqttUtils.hpp"
#include "Server.hpp"
#include "ShtUtils.hpp"
#include "TftUtils.hpp"
#include "ThermostatManager.hpp"
#include "WiFiUtils.hpp"

void setup() {
    Serial.begin(921600);
    Serial.println();
    LittleFS.begin();
    pinMode(RELAY_PIN, OUTPUT);
    thermostatOff();
    refreshShtMeasures(true);
    initTft();
    addEvent(EVENT_TYPES::CONNECTIVITY);
    dispatchEvent();
    initServer();
}

void loop() {
    refreshShtMeasures();
    mqttClient.loop();
    detectToutch();
    checkThermostatStatus();
    checkIfWiFiStatusHasChanged();
    server.handleClient();
    dispatchEvent();
    refreshMqttData();
    MDNS.update();
}