#ifndef __SHT_UTILS_H
#define __SHT_UTILS_H

#include <WEMOS_SHT3X.h>

#include "MqttUtils.hpp"

SHT3X sht30(0x45);

unsigned long NEXT_LOAD_SENSOR_TIME = millis();
unsigned long NEXT_LOAD_SENSOR_PERIOD = 60000;

void refreshData() {
    if (NEXT_LOAD_SENSOR_TIME < millis()) {
        sht30.get();
        publishTemperature(sht30.cTemp);
        publishHumidity(sht30.humidity);
        NEXT_LOAD_SENSOR_TIME = millis() + NEXT_LOAD_SENSOR_PERIOD;
    }
}

float getTemperature() {
    refreshData();
    return sht30.cTemp;
}

float getHumidity() {
    refreshData();
    return sht30.humidity;
}

#endif