#ifndef __EVENT_UTILS_H
#define __EVENT_UTILS_H

#include <queue>

enum EVENT_TYPES { ROOM_MEASURES,
                   TARGET_TEMPERATURE,
                   MODE,
                   ACTION,
                   CONNECTIVITY,
                   CONFIG_WIFI,
                   CONFIG_MQTT,
                   REBOOT,
                   RESET };

String EVENT_TYPES_DESCRIPTION[] = {"ROOM_MEASURES", "TARGET_TEMPERATURE", "MODE", "ACTION", "CONECTIVITY", "CONFIG_WIFI"};

std::queue<EVENT_TYPES> EVENTS;

void addEvent(EVENT_TYPES eventType) {
    EVENTS.push(eventType);
    Serial.println("EventUtils.hpp\t\t\tAdded event: " + EVENT_TYPES_DESCRIPTION[eventType]);
}

#endif