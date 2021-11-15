#ifndef __WIFI_UTILS_H
#define __WIFI_UTILS_H

#include <ESP8266WiFi.h>
#include <LittleFS.h>

#include "TftUtils.hpp"

String ssid = "";
String password = "";

String WIFI_STATUS[] = {"WL_IDLE_STATUS", "WL_NO_SSID_AVAIL", "WL_SCAN_COMPLETED", "WL_CONNECTED", "WL_CONNECT_FAILED", "WL_CONNECTION_LOST", "WL_WRONG_PASSWORD", "WL_DISCONNECTED"};

void checkConnectionWiFi_STA() {
    drawWifiButton();
    if (WiFi.waitForConnectResult() == WL_CONNECTED) {
        Serial.print("STA running:\t");
        Serial.println(ssid);
        Serial.print("IP address:\t");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("Connection with " + ssid + " failed");
        ssid = "";
        password = "";
    }
}

void connectWiFi_STA_fromFlash() {
    ssid = WiFi.SSID();
    Serial.println("");
    Serial.println("Connecting from flash to " + ssid);
    WiFi.begin();
    checkConnectionWiFi_STA();
}

void connectWiFi_STA_fromConfig() {
    ssid = "INVALID";
    password = "AXWG*3f9d1c";
    Serial.println("");
    Serial.println("Connecting from config to " + ssid);
    WiFi.begin(ssid, password);
    checkConnectionWiFi_STA();
}

/*
void connectWiFi_AP() {
    Serial.println("");
    Serial.println("Creating AP: ");
    String ssidAP = "ESP_SHT_CONFIG";
    IPAddress ip(192, 168, 2, 1);
    IPAddress gateway(192, 168, 2, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(ip, gateway, subnet);
    while (!WiFi.softAP(ssidAP)) {
        Serial.println(".");
        delay(100);
    }
    Serial.print("AP running:\t");
    Serial.println(ssidAP);
    Serial.print("IP address:\t");
    Serial.println(WiFi.softAPIP());
}*/

boolean existWifiConfig() {
    return LittleFS.exists("/config/wifi");
}

void loadWifiConfig() {
    if (existWifiConfig()) {
        File configWifi = LittleFS.open("/config/wifi", "r");
        ssid = configWifi.readStringUntil('\n');
        ssid.remove(ssid.length() - 1);
        password = configWifi.readStringUntil('\n');
        password.remove(password.length() - 1);
        configWifi.close();
    }
}

void writeWifiConfig() {
    File configWifi = LittleFS.open("/config/wifi", "w+");
    configWifi.println(ssid);
    configWifi.println(password);
    configWifi.close();
}

void configWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    WiFi.printDiag(Serial);
}

void connectWiFi() {
    if (thermostatData.isConectivityActive()) {
        configWiFi();
        connectWiFi_STA_fromFlash();
        if (WiFi.status() != WL_CONNECTED) {
            loadWifiConfig();
            connectWiFi_STA_fromConfig();
        }
    }
}

void disconnectWiFi() {
    WiFi.disconnect();
}

#endif