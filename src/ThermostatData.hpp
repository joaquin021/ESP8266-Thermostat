#ifndef __THERMOSTAT_DATA_H
#define __THERMOSTAT_DATA_H

#include <string>

class ThermostatData {
   private:
    float hotTolerance = 0.5;
    float coldTolerance = 0.5;
    float changeTemperatureValue = 0.5;
    float targetTemp = 21;
    std::string action = "off";
    char mode[5] = "off";

   public:
    float getHotTolerance();
    float getColdTolerance();
    float getTargetTemp();
    void setTargetTemp(float newTargetTemp);
    void increaseTargetTemp();
    void decreaseTargetTemp();
    std::string getAction();
    void setAction(std::string newAction);
    char *getMode();
    void changeMode(const char *newMode, unsigned int maxlen);
};

#endif