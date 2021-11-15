#ifndef __MQTT_UTILS_H
#define __MQTT_UTILS_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "EventUtils.hpp"

WiFiClient espClient;
PubSubClient mqttClient(espClient);

unsigned long NEXT_REFRESH_TIME = millis();
unsigned long NEXT_REFRESH_PERIOD = 300000;

String topicPrefix = "thermostat2/";
String topicChangeMode = "change/mode";
String topicChangeTargetTemperature = "change/targetTemperature";
String topicTemperature = "temperature";
String topicHumidity = "humidity";
String topicTargetTemperature = "targetTemperature";
String topicAvailability = "availability";
String topicMode = "mode";
String topicAction = "action";

const char* getCompleteTopicName(String topic) {
    if (!topicPrefix.equals("")) {
        topic = topicPrefix + topic;
    }
    return topic.c_str();
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.printf("MqttUtils.hpp\t\t\tMessage arrived [%s]\n", topic);
    if (strcmp(topic, getCompleteTopicName(topicChangeMode)) == 0) {
        thermostatData.changeMode(payload, length);
        addEvent(EVENT_TYPES::MODE);
    } else if (strcmp(topic, getCompleteTopicName(topicChangeTargetTemperature)) == 0) {
        char auxTargetTemp[length];
        memcpy(&auxTargetTemp, payload, length);
        auxTargetTemp[length] = '\0';
        thermostatData.setTargetTemp(String(auxTargetTemp).toFloat());
        addEvent(EVENT_TYPES::TARGET_TEMPERATURE);
    }
}

void checkAndconnectToMqttServer() {
    if (WiFi.status() == WL_CONNECTED && (mqttClient.state() != 0 || !mqttClient.connected())) {
        Serial.println("MqttUtils.hpp\t\t\tAttempting MQTT connection...");
        mqttClient.setServer("192.168.1.21", 1883);
        for (int i = 0; i < 5 && !mqttClient.connected(); i++) {
            Serial.printf("MqttUtils.hpp\t\t\tAttemping %i\n", i);
            if (mqttClient.connect("ESP8266_Thermostat", "mqtt_user", "pass")) {
                Serial.println("MqttUtils.hpp\t\t\tConnected to MQTT server");
                mqttClient.subscribe(getCompleteTopicName(topicChangeMode));
                mqttClient.subscribe(getCompleteTopicName(topicChangeTargetTemperature));
                mqttClient.setCallback(callback);
            } else {
                Serial.printf("MqttUtils.hpp\t\t\tfailed, rc=%i\n", mqttClient.state());
                delay(1000);
            }
        }
    }
}

void mqttPublish(const char* topic, const char* payload, bool ignoreConectivityStatus = false) {
    if (ignoreConectivityStatus || thermostatData.isConectivityActive()) {
        checkAndconnectToMqttServer();
        mqttClient.publish(topic, payload);
        Serial.printf("MqttUtils.hpp\t\t\tPublish message: %s in topic: %s\n", payload, topic);
    }
}

void publishTemperature() {
    char temperature[6];
    dtostrf(thermostatData.getTemperature(), 5, 2, temperature);
    mqttPublish(getCompleteTopicName(topicTemperature), temperature);
}

void publishHumidity() {
    checkAndconnectToMqttServer();
    char humidity[6];
    dtostrf(thermostatData.getHumidity(), 5, 2, humidity);
    mqttPublish(getCompleteTopicName(topicHumidity), humidity);
}

void publishTargetTemperature() {
    checkAndconnectToMqttServer();
    char temperature[6];
    dtostrf(thermostatData.getTargetTemp(), 5, 2, temperature);
    mqttPublish(getCompleteTopicName(topicTargetTemperature), temperature);
}

void publishStatus() {
    checkAndconnectToMqttServer();
    mqttPublish(getCompleteTopicName(topicAvailability), "online");
    mqttPublish(getCompleteTopicName(topicMode), thermostatData.getMode());
    mqttPublish(getCompleteTopicName(topicAction), thermostatData.getAction().c_str());
}

void refreshMqttData(bool force = false) {
    if (force || NEXT_REFRESH_TIME < millis()) {
        publishStatus();
        publishTargetTemperature();
        publishTemperature();
        publishHumidity();
        NEXT_REFRESH_TIME = millis() + NEXT_REFRESH_PERIOD;
    }
}

void disconnectMqtt() {
    checkAndconnectToMqttServer();
    mqttPublish(getCompleteTopicName(topicAvailability), "offline", true);
    delay(500);
    Serial.println("MqttUtils.hpp\t\t\tDisconnect Mqtt");
    mqttClient.disconnect();
}

#endif