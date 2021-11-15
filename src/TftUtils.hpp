#ifndef __TFT_UTILS_H
#define __TFT_UTILS_H

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ESP8266WiFi.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <XPT2046_Touchscreen.h>

#include <string>

#include "MqttUtils.hpp"
#include "ShtUtils.hpp"
#include "usergraphics.h"

#define TFT_CS D0
#define TFT_DC D8
#define TFT_RST -1
#define TS_CS D3

#define ILI9341_ULTRA_DARKGREY 0x632C
/*______Assign pressure_______*/
#define MINPRESSURE 10
#define MAXPRESSURE 2000
/*_______Assigned______*/

/*____Calibrate TFT LCD_____*/
#define TS_MINX 370
#define TS_MINY 470
#define TS_MAXX 3700
#define TS_MAXY 3600
/*______End of Calibration______*/

#define MAX_TEMPERATURE 35
#define MIN_TEMPERATURE 8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen touch(TS_CS);

TS_Point tsPoint;
bool touchPressed = false;

int WIFI_STATUS_COLOR[] = {ILI9341_ULTRA_DARKGREY, ILI9341_ORANGE, ILI9341_DARKCYAN, ILI9341_WHITE, ILI9341_RED, ILI9341_PURPLE, ILI9341_RED, ILI9341_ULTRA_DARKGREY};

float lastRoomTemperaturePrinted = 0;
float lastTargetTempPrinted = 0;
int lastWifiStatus = -1;
std::string lastPowerButton = "";

void drawUpDownButton() {
    //up button
    tft.fillTriangle(215, 10, 230, 30, 200, 30, ILI9341_WHITE);
    //down button
    tft.fillTriangle(215, 230, 230, 210, 200, 210, ILI9341_WHITE);
}

void drawPowerButton() {
    if (lastPowerButton.compare(thermostatData.getMode()) != 0) {
        if (strcmp(thermostatData.getMode(), "heat") == 0) {
            tft.drawBitmap(100, 275, powerIcon, 40, 40, ILI9341_WHITE);
        } else {
            tft.drawBitmap(100, 275, powerIcon, 40, 40, ILI9341_RED);
        }
        lastPowerButton = thermostatData.getMode();
    }
}

void drawWifiButton() {
    int wifiStatus = WiFi.status();
    if (lastWifiStatus != wifiStatus) {
        tft.drawBitmap(10, 10, wifiIcon, 24, 24, WIFI_STATUS_COLOR[wifiStatus]);
        lastWifiStatus = wifiStatus;
    }
}

void updateTargetTemp() {
    if (lastTargetTempPrinted != thermostatData.getTargetTemp()) {
        int16_t x1, y1;
        uint16_t w, h;
        char targetTempAux[5];
        dtostrf(thermostatData.getTargetTemp(), 4, 1, targetTempAux);
        tft.fillRect(50, 96, 93, 50, ILI9341_BLACK);
        tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
        tft.setFont(&FreeSansBold24pt7b);
        tft.getTextBounds(targetTempAux, 53, 130, &x1, &y1, &w, &h);
        tft.setCursor(137 - w, 130);
        tft.print(targetTempAux);
        lastTargetTempPrinted = thermostatData.getTargetTemp();
    }
}

void updateRoomTemp(float temperature) {
    if (lastRoomTemperaturePrinted != temperature) {
        int16_t x1, y1;
        uint16_t w, h;
        char currentValue[5];
        dtostrf(temperature, 4, 1, currentValue);
        tft.fillRect(20, 200, 50, 21, ILI9341_ULTRA_DARKGREY);
        tft.setTextColor(ILI9341_WHITE, ILI9341_ULTRA_DARKGREY);
        tft.setFont(&FreeSansBold12pt7b);
        tft.getTextBounds(currentValue, 40, 219, &x1, &y1, &w, &h);
        tft.setCursor(66 - w, 219);
        tft.print(currentValue);
        lastRoomTemperaturePrinted = temperature;
    }
}

void updateCircleColor(float temperature) {
    //draw big circle
    unsigned char i;
    if (thermostatData.getAction().compare("heating") == 0) {
        for (i = 0; i < 10; i++)
            tft.drawCircle(120, 120, 80 + i, ILI9341_RED);
    } else if (thermostatData.getAction().compare("idle") == 0) {
        for (i = 0; i < 10; i++)
            tft.drawCircle(120, 120, 80 + i, ILI9341_GREEN);
    } else {
        for (i = 0; i < 10; i++)
            tft.drawCircle(120, 120, 80 + i, ILI9341_ULTRA_DARKGREY);
    }

    //draw small
    tft.fillCircle(60, 200, 45, ILI9341_ULTRA_DARKGREY);
    lastRoomTemperaturePrinted = 0;
    updateRoomTemp(temperature);
    //draw °C in big circle
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setFont(&FreeSansBold9pt7b);
    tft.setCursor(143, 100);
    tft.print("o");
    tft.setFont(&FreeSansBold24pt7b);
    tft.setCursor(153, 130);
    tft.print("C");

    // draw room and °C in small circle
    tft.setTextColor(ILI9341_WHITE, ILI9341_ULTRA_DARKGREY);
    tft.setFont(&FreeSansBold12pt7b);
    tft.setCursor(79, 219);
    tft.print("C");
    tft.drawCircle(73, 203, 2, ILI9341_WHITE);
    tft.drawCircle(73, 203, 3, ILI9341_WHITE);
    tft.setFont(&FreeSansBold9pt7b);
    tft.setCursor(33, 190);
    tft.print("Room");
    updateTargetTemp();
}

void drawMainScreen() {
    tft.fillScreen(ILI9341_BLACK);
    updateCircleColor(getTemperature());
    drawUpDownButton();
    drawPowerButton();
    drawWifiButton();
    updateTargetTemp();
    NEXT_LOAD_SENSOR_TIME = millis();
}

void refreshScreen(float temperature) {
    updateRoomTemp(temperature);
    updateTargetTemp();
    drawPowerButton();
    drawWifiButton();
}

void initTft() {
    tft.begin();
    tft.setRotation(2);
    touch.begin();
    touch.setRotation(1);
    drawMainScreen();
}

bool touchEvent() {
    tsPoint = touch.getPoint();
    delay(1);
    if (tsPoint.z > MINPRESSURE) {
        tsPoint.x = map(tsPoint.x, TS_MINX, TS_MAXX, 0, 320);
        tsPoint.y = map(tsPoint.y, TS_MINY, TS_MAXY, 0, 240);

        return true;
    }
    return false;
}

void detectButtons(int x, int y) {
    //up down temperature buttons
    if (x >= 200) {
        if (y <= 40) {
            if (thermostatData.getTargetTemp() < MAX_TEMPERATURE) {
                thermostatData.increaseTargetTemp();
                updateTargetTemp();
                publishTargetTemperature();
            }
        } else if (y >= 200 && y <= 240) {
            if (thermostatData.getTargetTemp() > MIN_TEMPERATURE) {
                thermostatData.decreaseTargetTemp();
                updateTargetTemp();
                publishTargetTemperature();
            }
        }
    }
    // power button
    else if (x >= 95 && x <= 145 && y >= 270) {
        if (strcmp(thermostatData.getMode(), "heat") == 0) {
            thermostatData.changeMode("off", 4);
        } else {
            thermostatData.changeMode("heat", 5);
        }
        drawPowerButton();
    }
    // wifi button
    else if (x <= 40 && y <= 40) {
        thermostatData.toggleConnectivity();
        drawWifiButton();
    }
}

void detectToutch() {
    if (touchEvent()) {
        int x = tsPoint.y;
        int y = tsPoint.x;
        if (touchPressed == false) {
            detectButtons(x, y);
        }
        touchPressed = true;
    } else {
        touchPressed = false;
    }
}

#endif