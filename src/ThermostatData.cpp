#include "ThermostatData.hpp"

#include <Arduino.h>
#include <LittleFS.h>

#include <cstring>

float ThermostatData::getTemperature() { return temperature; }

void ThermostatData::setTemperature(float newTemperature) { temperature = newTemperature; }

float ThermostatData::getHumidity() { return humidity; }

void ThermostatData::setHumidity(float newHumidity) { humidity = newHumidity; }

float ThermostatData::getHotTolerance() { return hotTolerance; }

void ThermostatData::setHotTolerance(String newHotTolerance) {
    if (!newHotTolerance.isEmpty()) {
        Serial.println("ThermostatData.cpp\t\tSettig new hot tolerance.");
        hotTolerance = atof(newHotTolerance.c_str());
    }
}

float ThermostatData::getColdTolerance() { return coldTolerance; }

void ThermostatData::setColdTolerance(String newColdTolerance) {
    if (!newColdTolerance.isEmpty()) {
        Serial.println("ThermostatData.cpp\t\tSettig new cold tolerance.");
        coldTolerance = atof(newColdTolerance.c_str());
    }
}

float ThermostatData::getTargetTemp() { return targetTemp; }

void ThermostatData::setTargetTemp(float newTargetTemp) {
    targetTemp = newTargetTemp;
}

void ThermostatData::increaseTargetTemp() { targetTemp = targetTemp + temperatureStep; }

void ThermostatData::decreaseTargetTemp() { targetTemp = targetTemp - temperatureStep; }

void ThermostatData::setTemperatureStep(String newTemperatureStep) {
    if (!newTemperatureStep.isEmpty()) {
        Serial.println("ThermostatData.cpp\t\tSettig new temperature step.");
        temperatureStep = atof(newTemperatureStep.c_str());
    }
}

String ThermostatData::getAction() { return action; }

void ThermostatData::setAction(String newAction) { action = newAction; }

char *ThermostatData::getMode() { return mode; }

void ThermostatData::changeMode(const char *newMode, unsigned int length) {
    strncpy(mode, newMode, length - 1);
    mode[length - 1] = '\0';
}

void ThermostatData::changeMode(uint8_t *newMode, unsigned int length) {
    memcpy(mode, newMode, length);
    mode[length] = '\0';
}

bool ThermostatData::isConnectivityActive() { return connectivityActive; }

bool ThermostatData::toggleConnectivity() {
    connectivityActive = !connectivityActive;
    writeThermostatConfig();
    return connectivityActive;
}

bool ThermostatData::existThermostatConfig() {
    return LittleFS.exists("/config/thermostat");
}

void ThermostatData::loadThermostatConfig() {
    if (existThermostatConfig()) {
        Serial.println("ThermostatData.cpp\t\tLoad thermostat config.");
        File configThermostat = LittleFS.open("/config/thermostat", "r");
        String newHotTolerance = configThermostat.readStringUntil('\n');
        newHotTolerance.remove(newHotTolerance.length() - 1);
        String newColdTolerance = configThermostat.readStringUntil('\n');
        newColdTolerance.remove(newColdTolerance.length() - 1);
        String newTemperatureStep = configThermostat.readStringUntil('\n');
        newTemperatureStep.remove(newTemperatureStep.length() - 1);
        String newConnectivityActive = configThermostat.readStringUntil('\n');
        newConnectivityActive.remove(newConnectivityActive.length() - 1);
        connectivityActive = atoi(newConnectivityActive.c_str()) != 0;
        configThermostat.close();
        setHotTolerance(newHotTolerance);
        setColdTolerance(newColdTolerance);
        setTemperatureStep(newTemperatureStep);
    }
}

void ThermostatData::writeThermostatConfig() {
    Serial.println("ThermostatData.cpp\t\tWrite thermostat config.");
    File configThermostat = LittleFS.open("/config/thermostat", "w+");
    configThermostat.println(hotTolerance);
    configThermostat.println(coldTolerance);
    configThermostat.println(temperatureStep);
    configThermostat.println(connectivityActive);
    configThermostat.close();
}

void ThermostatData::deleteThermostatConfig() {
    Serial.println("ThermostatData.cpp\t\tDelete thermostat config.");
    LittleFS.remove("/config/thermostat");
}

String ThermostatData::toJson() {
    return String("{\"temperature\": \"") + temperature +
           "\", \"humidity\": \"" + humidity +
           "\",\"hotTolerance\": \"" + hotTolerance +
           "\",\"coldTolerance\": \"" + coldTolerance +
           "\",\"temperatureStep\": \"" + temperatureStep +
           "\",\"targetTemp\": \"" + targetTemp +
           "\",\"action\": \"" + action +
           "\",\"mode\": \"" + mode +
           "\",\"connectivityActive\": \"" + connectivityActive + "\"}";
}