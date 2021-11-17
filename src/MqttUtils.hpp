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

String topicPrefix = "";
String newTopicPrefix = "";
String changeModeTopic = "thermostat/change/mode";
String changeTargetTemperatureTopic = "thermostat/change/targetTemperature";
String temperatureTopic = "thermostat/temperature";
String humidityTopic = "thermostat/humidity";
String targetTemperatureTopic = "thermostat/targetTemperature";
String availabilityTopic = "thermostat/availability";
String modeTopic = "thermostat/mode";
String actionTopic = "thermostat/action";

boolean existTopicsConfig() {
    return LittleFS.exists("/config/topics");
}

void loadTopicsConfig() {
    if (existTopicsConfig()) {
        Serial.println("MqttUtils.hpp\t\t\tLoad Topics config.");
        File configTopics = LittleFS.open("/config/topics", "r");
        topicPrefix = configTopics.readStringUntil('\n');
        topicPrefix.remove(topicPrefix.length() - 1);
        configTopics.close();
    }
}

void writeTopicsConfig() {
    if (!newTopicPrefix.equals("")) {
        Serial.println("MqttUtils.hpp\t\t\tWrite Topics config.");
        File configTopics = LittleFS.open("/config/topics", "w+");
        configTopics.println(newTopicPrefix);
        configTopics.close();
        newTopicPrefix = "";
    }
}

boolean existMqttConfig() {
    return LittleFS.exists("/config/mqtt");
}

void loadMqttConfig() {
    if (existMqttConfig()) {
        Serial.println("MqttUtils.hpp\t\t\tLoad Mqtt config.");
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
        Serial.println("MqttUtils.hpp\t\t\tWrite Mqtt config.");
        File configMqtt = LittleFS.open("/config/mqtt", "w+");
        configMqtt.println(newMqttConfig->server);
        configMqtt.println(newMqttConfig->port);
        configMqtt.println(newMqttConfig->clientId);
        configMqtt.println(newMqttConfig->user);
        configMqtt.println(newMqttConfig->password);
        configMqtt.close();
        newMqttConfig = NULL;
    }
    writeTopicsConfig();
}

const char* getCompleteTopicName(String topic) {
    if (!topicPrefix.equals("")) {
        topic = topicPrefix + topic;
    }
    return topic.c_str();
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.printf("MqttUtils.hpp\t\t\tMessage arrived [%s]\n", topic);
    if (strcmp(topic, getCompleteTopicName(changeModeTopic)) == 0) {
        thermostatData.changeMode(payload, length);
        addEvent(EVENT_TYPES::MODE);
    } else if (strcmp(topic, getCompleteTopicName(changeTargetTemperatureTopic)) == 0) {
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
        loadTopicsConfig();
        if (actualMqttConfig != NULL) {
            Serial.println("MqttUtils.hpp\t\t\tAttempting MQTT connection...");
            mqttClient.setServer(actualMqttConfig->server.c_str(), actualMqttConfig->port);
            if (mqttClient.connect(actualMqttConfig->clientId.c_str(), actualMqttConfig->user.c_str(), actualMqttConfig->password.c_str())) {
                Serial.println("MqttUtils.hpp\t\t\tConnected to MQTT server");
                mqttClient.subscribe(getCompleteTopicName(changeModeTopic));
                mqttClient.subscribe(getCompleteTopicName(changeTargetTemperatureTopic));
                mqttClient.setCallback(callback);
            } else {
                Serial.printf("MqttUtils.hpp\t\t\tfailed, rc=%i\n", mqttClient.state());
            }
        }
    }
    return mqttClient.connected();
}

void mqttPublish(String topic, const char* payload, bool ignoreConectivityStatus = false) {
    if (ignoreConectivityStatus || thermostatData.isConnectivityActive()) {
        if (checkAndconnectToMqttServer()) {
            mqttClient.publish(getCompleteTopicName(topic), payload);
            Serial.printf("MqttUtils.hpp\t\t\tPublish message: %s in topic: %s\n", payload, getCompleteTopicName(topic));
        }
    }
}

void publishTemperature() {
    char temperature[6];
    dtostrf(thermostatData.getTemperature(), 5, 2, temperature);
    mqttPublish(temperatureTopic, temperature);
}

void publishHumidity() {
    char humidity[6];
    dtostrf(thermostatData.getHumidity(), 5, 2, humidity);
    mqttPublish(humidityTopic, humidity);
}

void publishTargetTemperature() {
    char temperature[6];
    dtostrf(thermostatData.getTargetTemp(), 5, 2, temperature);
    mqttPublish(targetTemperatureTopic, temperature);
}

void publishStatus() {
    mqttPublish(availabilityTopic, "online");
    mqttPublish(modeTopic, thermostatData.getMode());
    mqttPublish(actionTopic, thermostatData.getAction().c_str());
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
    mqttPublish(availabilityTopic, "offline", true);
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
    LittleFS.remove("/config/topics");
}

String getTopicsData() {
    return String("{\"topicPrefix\": \"") + topicPrefix +
           "\", \"changeModeTopic\": \"" + getCompleteTopicName(changeModeTopic) +
           "\",\"changeTargetTemperatureTopic\": \"" + getCompleteTopicName(changeTargetTemperatureTopic) +
           "\",\"temperatureTopic\": \"" + getCompleteTopicName(temperatureTopic) +
           "\",\"humidityTopic\": \"" + getCompleteTopicName(humidityTopic) +
           "\",\"targetTemperatureTopic\": \"" + getCompleteTopicName(targetTemperatureTopic) +
           "\",\"availabilityTopic\": \"" + getCompleteTopicName(availabilityTopic) +
           "\",\"modeTopic\": \"" + getCompleteTopicName(modeTopic) +
           "\",\"actionTopic\": \"" + getCompleteTopicName(actionTopic) + "\"}";
}

#endif