#include "ThermostatData.hpp"

#include <cstring>
using namespace std;

float ThermostatData::getHotTolerance() { return hotTolerance; }

float ThermostatData::getColdTolerance() { return coldTolerance; }

float ThermostatData::getTargetTemp() { return targetTemp; }

void ThermostatData::increaseTargetTemp() { targetTemp = targetTemp + changeTemperatureValue; }

void ThermostatData::decreaseTargetTemp() { targetTemp = targetTemp - changeTemperatureValue; }

string ThermostatData::getAction() { return action; }

void ThermostatData::setAction(string newAction) { action = newAction; }

char *ThermostatData::getMode() { return mode; }

void ThermostatData::changeMode(const char *newMode, unsigned int maxlen) {
    strncpy(mode, newMode, maxlen - 1);
    mode[maxlen - 1] = '\0';
}