SHT3X sht30(0x45);

unsigned long NEXT_LOAD_SENSOR_TIME = millis();
unsigned long NEXT_LOAD_SENSOR_PERIOD = 10000;

void refreshData() {
    if (NEXT_LOAD_SENSOR_TIME < millis()) {
        sht30.get();
        NEXT_LOAD_SENSOR_TIME = millis() + NEXT_LOAD_SENSOR_PERIOD;
    }
}

float getTemperature() {
    refreshData();
    return sht30.cTemp;
}

float getHumidity() {
    refreshData();
    return sht30.humidity;
}