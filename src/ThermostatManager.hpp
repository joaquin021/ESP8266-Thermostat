#ifndef __THERMOSTAT_MANAGER_H
#define __THERMOSTAT_MANAGER_H

#include "MqttUtils.hpp"
#include "ShtUtils.hpp"
#include "TftUtils.hpp"
#include "WiFiUtils.hpp"

#define RELAY_PIN D4

boolean lastConnectivityActive = thermostatData.isConectivityActive();

boolean temperatureAboveTarget(float temperature) {
    return temperature > thermostatData.getTargetTemp() + thermostatData.getHotTolerance();
}

boolean temperatureBelowTarget(float temperature) {
    return temperature < thermostatData.getTargetTemp() - thermostatData.getColdTolerance();
}

void checkChangesInConnectivity() {
    if (lastConnectivityActive != thermostatData.isConectivityActive()) {
        if (thermostatData.isConectivityActive()) {
            connectWiFi();
            checkAndconnectToMqttServer();
            publishStatus();
            publishTargetTemperature();
            publishTemperature(getTemperature());
            publishHumidity(getHumidity());
        } else {
            disconnectMqtt();
            disconnectWiFi();
        }
        lastConnectivityActive = thermostatData.isConectivityActive();
    }
}

void thermostat() {
    float temperature = getTemperature();
    if (strcmp(thermostatData.getMode(), "heat") == 0) {
        if (thermostatData.getAction().compare("idle") != 0 && temperatureAboveTarget(temperature)) {
            digitalWrite(RELAY_PIN, LOW);
            thermostatData.setAction("idle");
            updateCircleColor(temperature);
            publishStatus();
        } else if (thermostatData.getAction().compare("heating") != 0 && temperatureBelowTarget(temperature)) {
            digitalWrite(RELAY_PIN, HIGH);
            thermostatData.setAction("heating");
            updateCircleColor(temperature);
            publishStatus();
        } else if (thermostatData.getAction().compare("off") == 0) {
            digitalWrite(RELAY_PIN, LOW);
            thermostatData.setAction("idle");
            updateCircleColor(temperature);
        }
    } else if (thermostatData.getAction().compare("off") != 0) {
        digitalWrite(RELAY_PIN, LOW);
        thermostatData.setAction("off");
        updateCircleColor(temperature);
        publishStatus();
    }
    refreshScreen(temperature);
    refreshMqttData();
    checkChangesInConnectivity();
}

#endif