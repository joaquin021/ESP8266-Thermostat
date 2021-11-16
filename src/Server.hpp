#ifndef __SERVER_H
#define __SERVER_H

#include <ESP8266WebServer.h>

#include "EventUtils.hpp"
#include "WiFiUtils.hpp"
#include "web/asset.h"
#include "web/html.h"
#include "web/lib.h"
#include "web/vendor.h"

ESP8266WebServer server(80);

void handleNotFound() {
    server.send(404, "text/plain", "Not found");
}

void handleHtml() {
    server.on("/", []() {
        server.send_P(200, "text/html", MAIN_page);
    });
    server.on("/config-wifi.html", []() {
        server.send_P(200, "text/html", CONFIG_WIFI_HTML);
    });
    server.on("/favicon.ico", []() {
        server.send_P(200, "image/x-icon", FAVICON, sizeof(FAVICON));
    });
}

void handleAsset() {
    server.on("/asset/espconfig.css", []() {
        server.send_P(200, "text/css", ESP_CONFIG_CSS);
    });
}

void handleLib() {
    server.on("/lib/home.js", []() {
        server.send_P(200, "application/javascript", HOME_JS);
    });
    server.on("/lib/espconfig.js", []() {
        server.send_P(200, "application/javascript", ESP_CONFIG_JS);
    });
}

void handleVendor() {
    server.on("/vendor/material.css", []() {
        server.send_P(200, "text/css", MATERIAL_CSS_MIN);
    });
    server.on("/vendor/material.js", []() {
        server.send_P(200, "application/javascript", MATERIAL_JS_MIN);
    });
    server.on("/vendor/google-fonts.css", []() {
        server.send_P(200, "text/css", GOOGLE_FONTS);
    });
    server.on("/vendor/flUhRq6.woff2", []() {
        server.send_P(200, "font/woff2", flUhRq6, sizeof(flUhRq6));
    });
    server.on("/vendor/KFOmC.woff2", []() {
        server.send_P(200, "font/woff2", KFOmC, sizeof(KFOmC));
    });
}

void handleWiFiConfig() {
    server.on("/checkWifiStatus", []() {
        server.send(200, "text/plain", getWifiStatus());
    });
    server.on("/getWifiConfig", []() {
        server.send(200, "application/json", "{\"ssid\": \"" + ssid + "\", \"ip\": \"" + WiFi.localIP().toString() + "\", \"apIp\": \"" + WiFi.softAPIP().toString() + "\"}");
    });
    server.on("/setWifiConfig", []() {
        ssid = server.arg("ssid");
        password = server.arg("password");
        addEvent(EVENT_TYPES::CONFIG_WIFI);
        server.sendHeader("Location", "/");
        server.sendHeader("Cache-Control", "no-cache");
        server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
        server.send(301);
    });
}

void initServer() {
    handleHtml();
    handleAsset();
    handleLib();
    handleVendor();
    handleWiFiConfig();
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("Server.hpp\t\t\tHTTP server started.");
}

#endif