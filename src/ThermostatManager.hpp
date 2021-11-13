#define MAX_TEMPERATURE 28
#define MIN_TEMPERATURE 18
#define RELAY_PIN D4

boolean temperatureAboveTarget(float temperature)
{
    return temperature >= thermostatData.targetTemp + thermostatData.hotTolerance;
}

boolean temperatureBelowTarget(float temperature)
{
    return temperature <= thermostatData.targetTemp - thermostatData.coldTolerance;
}

boolean temperatureBetweenToleranceRange(float temperature)
{
    return temperature < thermostatData.targetTemp + thermostatData.hotTolerance && temperature > thermostatData.targetTemp - thermostatData.coldTolerance;
}

void thermostat()
{
    float temperature = getTemperature();
    //float humidity = getHumidity();
    if (strcmp(thermostatData.mode, "heat") == 0)
    {
        if (!thermostatData.action.equals("idle") && (temperatureAboveTarget(temperature) || temperatureBetweenToleranceRange(temperature)))
        {
            digitalWrite(RELAY_PIN, LOW);
            thermostatData.action = "idle";
            updateCircleColor(temperature);
            //publishActionAndMode();
        }
        else if (!thermostatData.action.equals("heating") && temperatureBelowTarget(temperature))
        {
            digitalWrite(RELAY_PIN, HIGH);
            thermostatData.action = "heating";
            updateCircleColor(temperature);
            //publishActionAndMode();
        }
    }
    else if (!thermostatData.action.equals("off"))
    {
        digitalWrite(RELAY_PIN, LOW);
        thermostatData.action = "off";
        updateCircleColor(temperature);
        //publishActionAndMode();
    }
    //publishTemperature();
    //publishHumidity();
    updateRoomTemp(temperature);
    //publishActionAndMode();
}