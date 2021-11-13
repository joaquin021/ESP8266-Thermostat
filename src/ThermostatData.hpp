class ThermostatData
{
public:
    float hotTolerance = 0.5;
    float coldTolerance = 0.5;
    float targetTemp = 21;
    String action = "off";
    char mode[5] = "off";
};
