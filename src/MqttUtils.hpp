#ifndef __MQTT_UTILS_H
#define __MQTT_UTILS_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

unsigned long NEXT_REFRESH_TIME = millis();
unsigned long NEXT_REFRESH_PERIOD = 300000;

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.printf("Message arrived [%s]\n", topic);
    if (strcmp(topic, "thermostat2/change/mode") == 0) {
        thermostatData.changeMode(payload, length);
    } else if (strcmp(topic, "thermostat2/change/targetTemperature") == 0) {
        char auxTargetTemp[length];
        memcpy(&auxTargetTemp, payload, length);
        auxTargetTemp[length] = '\0';
        thermostatData.setTargetTemp(String(auxTargetTemp).toFloat());
    }
}

void checkAndconnectToMqttServer() {
    if (WiFi.status() == WL_CONNECTED && (mqttClient.state() != 0 || !mqttClient.connected())) {
        Serial.println("Attempting MQTT connection...");
        mqttClient.setServer("192.168.1.21", 1883);
        for (int i = 0; i < 5 && !mqttClient.connected(); i++) {
            Serial.printf("Attemping %i\n", i);
            if (mqttClient.connect("thermostat2", "XX", "XX")) {
                Serial.println("Connected to MQTT server");
                mqttClient.subscribe("thermostat2/change/mode");
                mqttClient.subscribe("thermostat2/change/targetTemperature");
                mqttClient.setCallback(callback);
            } else {
                Serial.printf("failed, rc=%i\n", mqttClient.state());
                delay(1000);
            }
        }
    }
}

void mqttPublish(const char* topic, const char* payload, bool ignoreConectivityStatus = false) {
    if (ignoreConectivityStatus || thermostatData.isConectivityActive()) {
        checkAndconnectToMqttServer();
        mqttClient.publish(topic, payload);
        Serial.printf("Publish message: %s in topic: %s\n", payload, topic);
    }
}

void publishTemperature(float t) {
    char temperature[6];
    dtostrf(t, 5, 2, temperature);
    mqttPublish("thermostat2/temperature", temperature);
}

void publishHumidity(float h) {
    checkAndconnectToMqttServer();
    char humidity[6];
    dtostrf(h, 5, 2, humidity);
    mqttPublish("thermostat2/humidity", humidity);
}

void publishTargetTemperature() {
    checkAndconnectToMqttServer();
    char temperature[6];
    dtostrf(thermostatData.getTargetTemp(), 5, 2, temperature);
    mqttPublish("thermostat2/targetTemperature", temperature);
}

void publishStatus() {
    checkAndconnectToMqttServer();
    mqttPublish("thermostat2/availability", "online");
    mqttPublish("thermostat2/mode", thermostatData.getMode());
    mqttPublish("thermostat2/action", thermostatData.getAction().c_str());
}

void refreshMqttData() {
    if (NEXT_REFRESH_TIME < millis()) {
        publishStatus();
        publishTargetTemperature();
        NEXT_REFRESH_TIME = millis() + NEXT_REFRESH_PERIOD;
    }
}

void disconnectMqtt() {
    checkAndconnectToMqttServer();
    mqttPublish("thermostat2/availability", "offline", true);
    delay(500);
    mqttClient.disconnect();
}

#endif