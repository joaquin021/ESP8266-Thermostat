#include "ThermostatData.hpp"

#include <Arduino.h>

#include <cstring>
using namespace std;

float ThermostatData::getTemperature() { return temperature; }

void ThermostatData::setTemperature(float newTemperature) { temperature = newTemperature; }

float ThermostatData::getHumidity() { return humidity; }

void ThermostatData::setHumidity(float newHumidity) { humidity = newHumidity; }

float ThermostatData::getHotTolerance() { return hotTolerance; }

float ThermostatData::getColdTolerance() { return coldTolerance; }

float ThermostatData::getTargetTemp() { return targetTemp; }

void ThermostatData::setTargetTemp(float newTargetTemp) {
    targetTemp = newTargetTemp;
}

void ThermostatData::increaseTargetTemp() { targetTemp = targetTemp + temperatureStep; }

void ThermostatData::decreaseTargetTemp() { targetTemp = targetTemp - temperatureStep; }

string ThermostatData::getAction() { return action; }

void ThermostatData::setAction(string newAction) { action = newAction; }

char *ThermostatData::getMode() { return mode; }

void ThermostatData::changeMode(const char *newMode, unsigned int length) {
    strncpy(mode, newMode, length - 1);
    mode[length - 1] = '\0';
}

void ThermostatData::changeMode(uint8_t *newMode, unsigned int length) {
    memcpy(mode, newMode, length);
    mode[length] = '\0';
}

bool ThermostatData::isConectivityActive() { return conectivityActive; }
bool ThermostatData::toggleConnectivity() {
    conectivityActive = !conectivityActive;
    return conectivityActive;
}