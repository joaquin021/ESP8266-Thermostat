#ifndef __WIFI_UTILS_H
#define __WIFI_UTILS_H

#include <Adafruit_ILI9341.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>

#include "EventUtils.hpp"

String ssid = "";
String password = "";

String WIFI_STATUS[] = {"WL_IDLE_STATUS", "WL_NO_SSID_AVAIL", "WL_SCAN_COMPLETED", "WL_CONNECTED", "WL_CONNECT_FAILED", "WL_CONNECTION_LOST", "WL_WRONG_PASSWORD", "WL_DISCONNECTED"};
int WIFI_STATUS_COLOR[] = {ILI9341_ULTRA_DARKGREY, ILI9341_ORANGE, ILI9341_BLUE, ILI9341_WHITE, ILI9341_RED, ILI9341_YELLOW, ILI9341_RED, ILI9341_ULTRA_DARKGREY};
int WIFI_WORKING_COLOR = ILI9341_DARKCYAN;

int lastWiFiStatus = -1;
int lastWiFiConnectionErrorStatus = -1;

boolean existWifiConfig() {
    return LittleFS.exists("/config/wifi");
}

void loadWifiConfig() {
    if (existWifiConfig()) {
        Serial.println("WiFiUtils.hpp\t\t\tLoad WiFi config.");
        File configWifi = LittleFS.open("/config/wifi", "r");
        ssid = configWifi.readStringUntil('\n');
        ssid.remove(ssid.length() - 1);
        password = configWifi.readStringUntil('\n');
        password.remove(password.length() - 1);
        configWifi.close();
    }
}

void writeWifiConfig() {
    Serial.println("WiFiUtils.hpp\t\t\tWrite WiFi config.");
    File configWifi = LittleFS.open("/config/wifi", "w+");
    configWifi.println(ssid);
    configWifi.println(password);
    configWifi.close();
}

void deleteWiFiConfig() {
    Serial.println("WiFiUtils.hpp\t\t\tDelete WiFi config.");
    LittleFS.remove("/config/wifi");
    WiFi.disconnect();
}

void checkConnectionWiFi_STA() {
    if (WiFi.waitForConnectResult() == WL_CONNECTED) {
        Serial.println("WiFiUtils.hpp\t\t\tSTA running:\t" + ssid);
        Serial.print("WiFiUtils.hpp\t\t\tIP address:\t");
        Serial.println(WiFi.localIP());
        lastWiFiConnectionErrorStatus = -1;
    } else {
        Serial.println("WiFiUtils.hpp\t\t\tConnection with " + ssid + " failed");
        ssid = "";
        password = "";
        lastWiFiConnectionErrorStatus = WiFi.status();
        WiFi.disconnect();
    }
}

void connectWiFi_STA_fromFlash() {
    ssid = WiFi.SSID();
    Serial.println("WiFiUtils.hpp\t\t\tConnecting from flash to " + ssid);
    WiFi.begin();
    checkConnectionWiFi_STA();
}

void connectWiFi_STA_fromConfig() {
    loadWifiConfig();
    if (!ssid.equals("") && !password.equals("")) {
        Serial.println("WiFiUtils.hpp\t\t\tConnecting from config to " + ssid);
        WiFi.begin(ssid, password);
        checkConnectionWiFi_STA();
        if (WiFi.status() != WL_CONNECTED) {
            deleteWiFiConfig();
        }
    } else {
        Serial.println("WiFiUtils.hpp\t\t\tNo configuration found for WiFi connection");
    }
}

void connectWiFi_AP() {
    Serial.println("");
    Serial.println("WiFiUtils.hpp\t\t\tCreating AP: ");
    WiFi.mode(WIFI_AP_STA);
    String ssidAP = "THERMOSTAT_CONFIG";
    IPAddress ip(192, 168, 4, 1);
    IPAddress gateway(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(ip, gateway, subnet);
    while (!WiFi.softAP(ssidAP)) {
        Serial.println(".");
        delay(100);
    }
    Serial.println("WiFiUtils.hpp\t\t\tAP running:\t" + ssidAP);
    Serial.println(ssidAP);
    Serial.print("WiFiUtils.hpp\t\t\tIP address:\t");
    Serial.println(WiFi.softAPIP());
}

void configWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
}

void configMdns() {
    if (MDNS.begin("thermostat")) {
        Serial.println("WiFiUtils.hpp\t\t\tMDNS responder started");
    }
}

void connectWiFi() {
    if (thermostatData.isConnectivityActive()) {
        configWiFi();
        connectWiFi_STA_fromFlash();
        if (WiFi.status() != WL_CONNECTED) {
            connectWiFi_STA_fromConfig();
            if (WiFi.status() != WL_CONNECTED) {
                connectWiFi_AP();
            }
        }
        configMdns();
        WiFi.printDiag(Serial);
    }
    addEvent(EVENT_TYPES::CONNECTIVITY);
    lastWiFiStatus = WiFi.status();
}

void disconnectWiFi() {
    Serial.println("WiFiUtils.hpp\t\t\tDisconnect WiFi.");
    WiFi.disconnect();
    WiFi.softAPdisconnect(true);
    lastWiFiConnectionErrorStatus = -1;
    lastWiFiStatus = WiFi.status();
}

void checkIfWiFiStatusHasChanged() {
    if (WiFi.status() != lastWiFiStatus) {
        addEvent(EVENT_TYPES::CONNECTIVITY);
        lastWiFiStatus = WiFi.status();
        if (WiFi.status() == WL_CONNECTED) {
            lastWiFiConnectionErrorStatus = -1;
        }
    }
}

int getWiFiStatusColor() {
    if (lastWiFiConnectionErrorStatus != -1) {
        return WIFI_STATUS_COLOR[lastWiFiConnectionErrorStatus];
    } else {
        return WIFI_STATUS_COLOR[WiFi.status()];
    }
}

String getWifiStatus() {
    if (lastWiFiConnectionErrorStatus != -1) {
        return WIFI_STATUS[lastWiFiConnectionErrorStatus];
    } else {
        return WIFI_STATUS[WiFi.status()];
    }
}

#endif