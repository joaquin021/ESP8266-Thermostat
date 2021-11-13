#ifndef __THERMOSTAT_MANAGER_H
#define __THERMOSTAT_MANAGER_H

#include "ShtUtils.hpp"
#include "TftUtils.hpp"

#define MAX_TEMPERATURE 28
#define MIN_TEMPERATURE 18
#define RELAY_PIN D4

boolean temperatureAboveTarget(float temperature) {
    return temperature > thermostatData.getTargetTemp() + thermostatData.getHotTolerance();
}

boolean temperatureBelowTarget(float temperature) {
    return temperature < thermostatData.getTargetTemp() - thermostatData.getColdTolerance();
}

void thermostat() {
    float temperature = getTemperature();
    //float humidity = getHumidity();
    if (strcmp(thermostatData.getMode(), "heat") == 0) {
        if (thermostatData.getAction().compare("idle") != 0 && temperatureAboveTarget(temperature)) {
            digitalWrite(RELAY_PIN, LOW);
            thermostatData.setAction("idle");
            updateCircleColor(temperature);
            //publishActionAndMode();
        } else if (thermostatData.getAction().compare("heating") != 0 && temperatureBelowTarget(temperature)) {
            digitalWrite(RELAY_PIN, HIGH);
            thermostatData.setAction("heating");
            updateCircleColor(temperature);
            //publishActionAndMode();
        } else if (thermostatData.getAction().compare("off") == 0) {
            digitalWrite(RELAY_PIN, LOW);
            thermostatData.setAction("idle");
            updateCircleColor(temperature);
        }
    } else if (thermostatData.getAction().compare("off") != 0) {
        digitalWrite(RELAY_PIN, LOW);
        thermostatData.setAction("off");
        updateCircleColor(temperature);
        //publishActionAndMode();
    }
    //publishTemperature();
    //publishHumidity();
    updateRoomTemp(temperature);
    //publishActionAndMode();
}

#endif