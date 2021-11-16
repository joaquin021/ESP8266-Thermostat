#ifndef __MQTT_UTILS_H
#define __MQTT_UTILS_H

#include <ESP8266WiFi.h>
#include <LittleFS.h>
#include <PubSubClient.h>

#include "EventUtils.hpp"

String MQTT_STATUS_POSITIVE[] = {"MQTT_CONNECTED", "MQTT_CONNECT_BAD_PROTOCOL", "MQTT_CONNECT_BAD_CLIENT_ID", "MQTT_CONNECT_UNAVAILABLE", "MQTT_CONNECT_BAD_CREDENTIALS", "MQTT_CONNECT_UNAUTHORIZED"};
String MQTT_STATUS_NEGATIVE[] = {"", "MQTT_DISCONNECTED", "MQTT_CONNECT_FAILED", "MQTT_CONNECTION_LOST", "MQTT_CONNECTION_TIMEOUT"};

class MqttConfig {
   public:
    String server;
    int port;
    String clientId;
    String user;
    String password;

    String toJson() {
        return String("{\"server\": \"") + server +
               "\", \"port\": \"" + port +
               "\",\"clientId\": \"" + clientId +
               "\",\"user\": \"" + user + "\"}";
    }
};
MqttConfig* actualMqttConfig = NULL;
MqttConfig* newMqttConfig = NULL;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

unsigned long NEXT_REFRESH_TIME = millis();
unsigned long NEXT_REFRESH_PERIOD = 300000;

String topicPrefix = "test-";
String topicChangeMode = "thermostat/change/mode";
String topicChangeTargetTemperature = "thermostat/change/targetTemperature";
String topicTemperature = "thermostat/temperature";
String topicHumidity = "thermostat/humidity";
String topicTargetTemperature = "thermostat/targetTemperature";
String topicAvailability = "thermostat/availability";
String topicMode = "thermostat/mode";
String topicAction = "thermostat/action";

boolean existMqttConfig() {
    return LittleFS.exists("/config/mqtt");
}

void loadMqttConfig() {
    if (existMqttConfig()) {
        Serial.println("WiFiUtils.hpp\t\t\tLoad Mqtt config.");
        actualMqttConfig = new MqttConfig();
        File configMqtt = LittleFS.open("/config/mqtt", "r");
        actualMqttConfig->server = configMqtt.readStringUntil('\n');
        actualMqttConfig->server.remove(actualMqttConfig->server.length() - 1);
        String port = configMqtt.readStringUntil('\n');
        port.remove(port.length() - 1);
        actualMqttConfig->port = atoi(port.c_str());
        actualMqttConfig->clientId = configMqtt.readStringUntil('\n');
        actualMqttConfig->clientId.remove(actualMqttConfig->clientId.length() - 1);
        actualMqttConfig->user = configMqtt.readStringUntil('\n');
        actualMqttConfig->user.remove(actualMqttConfig->user.length() - 1);
        actualMqttConfig->password = configMqtt.readStringUntil('\n');
        actualMqttConfig->password.remove(actualMqttConfig->password.length() - 1);
        configMqtt.close();
    }
}

void writeMqttConfig() {
    if (newMqttConfig != NULL) {
        Serial.println("WiFiUtils.hpp\t\t\tWrite Mqtt config.");
        File configMqtt = LittleFS.open("/config/mqtt", "w+");
        configMqtt.println(newMqttConfig->server);
        configMqtt.println(newMqttConfig->port);
        configMqtt.println(newMqttConfig->clientId);
        configMqtt.println(newMqttConfig->user);
        configMqtt.println(newMqttConfig->password);
        configMqtt.close();
        newMqttConfig = NULL;
    }
}

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

bool checkAndconnectToMqttServer() {
    if (WiFi.status() == WL_CONNECTED && (mqttClient.state() != 0 || !mqttClient.connected())) {
        loadMqttConfig();
        if (actualMqttConfig != NULL) {
            Serial.println("MqttUtils.hpp\t\t\tAttempting MQTT connection...");
            mqttClient.setServer(actualMqttConfig->server.c_str(), actualMqttConfig->port);
            if (mqttClient.connect(actualMqttConfig->clientId.c_str(), actualMqttConfig->user.c_str(), actualMqttConfig->password.c_str())) {
                Serial.println("MqttUtils.hpp\t\t\tConnected to MQTT server");
                mqttClient.subscribe(getCompleteTopicName(topicChangeMode));
                mqttClient.subscribe(getCompleteTopicName(topicChangeTargetTemperature));
                mqttClient.setCallback(callback);
            } else {
                Serial.printf("MqttUtils.hpp\t\t\tfailed, rc=%i\n", mqttClient.state());
            }
        }
    }
    return mqttClient.connected();
}

void mqttPublish(const char* topic, const char* payload, bool ignoreConectivityStatus = false) {
    if (ignoreConectivityStatus || thermostatData.isConectivityActive()) {
        if (checkAndconnectToMqttServer()) {
            mqttClient.publish(topic, payload);
            Serial.printf("MqttUtils.hpp\t\t\tPublish message: %s in topic: %s\n", payload, topic);
        }
    }
}

void publishTemperature() {
    char temperature[6];
    dtostrf(thermostatData.getTemperature(), 5, 2, temperature);
    mqttPublish(getCompleteTopicName(topicTemperature), temperature);
}

void publishHumidity() {
    char humidity[6];
    dtostrf(thermostatData.getHumidity(), 5, 2, humidity);
    mqttPublish(getCompleteTopicName(topicHumidity), humidity);
}

void publishTargetTemperature() {
    char temperature[6];
    dtostrf(thermostatData.getTargetTemp(), 5, 2, temperature);
    mqttPublish(getCompleteTopicName(topicTargetTemperature), temperature);
}

void publishStatus() {
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
    Serial.println("MqttUtils.hpp\t\t\tDisconnect Mqtt");
    mqttPublish(getCompleteTopicName(topicAvailability), "offline", true);
    delay(500);
    mqttClient.disconnect();
    actualMqttConfig = NULL;
}

String getMqttStatus() {
    int statusCode = mqttClient.state();
    return statusCode < 0 ? MQTT_STATUS_NEGATIVE[statusCode * -1] : MQTT_STATUS_POSITIVE[statusCode];
}

void deleteMqttConfig() {
    Serial.println("MqttUtils.hpp\t\t\tDelete Mqtt config.");
    disconnectMqtt();
    LittleFS.remove("/config/mqtt");
}

#endif