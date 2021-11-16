#ifndef __EVENTS_DISPATCHER_H
#define __EVENTS_DISPATCHER_H

#include <ESP8266mDNS.h>

#include <queue>

#include "EventUtils.hpp"
#include "MqttUtils.hpp"
#include "TftUtils.hpp"
#include "ThermostatManager.hpp"
#include "WiFiUtils.hpp"

boolean lastConnectivityActive = false;

void manageRoomMeasuresEvent() {
    updateRoomTemp();
    publishTemperature();
    publishHumidity();
}

void manageTargetTemperatureEvent() {
    updateTargetTemp();
    publishTargetTemperature();
}

void manageModeEvent() {
    drawPowerButton();
    publishStatus();
}

void manageActionEvent() {
    if (thermostatData.getAction().compare("heating") == 0) {
        thermostatHeating();
    } else {
        thermostatOff();
    }
    updateCircleColor();
    publishStatus();
}

void manageConnectivityEvent() {
    if (lastConnectivityActive != thermostatData.isConectivityActive()) {
        drawWiFiButton(WIFI_WORKING_COLOR);
        if (thermostatData.isConectivityActive()) {
            connectWiFi();
            refreshMqttData(true);
        } else {
            disconnectMqtt();
            disconnectWiFi();
        }
        lastConnectivityActive = thermostatData.isConectivityActive();
    }
    drawWiFiButton(getWiFiStatusColor());
}

void manageWiFiConfigEvent() {
    drawWiFiButton(WIFI_WORKING_COLOR);
    writeWifiConfig();
    connectWiFi_STA_fromConfig();
    configMdns();
    refreshMqttData(true);
    drawWiFiButton(getWiFiStatusColor());
}

void dispatchEvent() {
    if (!EVENTS.empty()) {
        Serial.println("EventsDispatcher.hpp\t\t########## Dispatching events ##########");
        while (!EVENTS.empty()) {
            EVENT_TYPES eventType = EVENTS.front();
            Serial.printf("EventsDispatcher.hpp\t\t---> Queue size: %i\n", EVENTS.size());
            Serial.println("EventsDispatcher.hpp\t\t---> Dispatch event: " + EVENT_TYPES_DESCRIPTION[eventType]);
            switch (eventType) {
                case EVENT_TYPES::ROOM_MEASURES:
                    manageRoomMeasuresEvent();
                    break;
                case EVENT_TYPES::TARGET_TEMPERATURE:
                    manageTargetTemperatureEvent();
                    break;
                case EVENT_TYPES::MODE:
                    manageModeEvent();
                    break;
                case EVENT_TYPES::ACTION:
                    manageActionEvent();
                    break;
                case EVENT_TYPES::CONNECTIVITY:
                    manageConnectivityEvent();
                    break;
                case EVENT_TYPES::CONFIG_WIFI:
                    manageWiFiConfigEvent();
                    break;
                default:
                    break;
            }
            EVENTS.pop();
        }
        Serial.println("EventsDispatcher.hpp\t\t########################################");
    }
}

#endif
