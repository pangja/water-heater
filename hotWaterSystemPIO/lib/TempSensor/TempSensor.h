#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
#include "OneWire.h"
#include "DallasTemperature.h"
#include "Arduino.h"

class TempSensor
{
private:
    int numberOfDevices;

public:
    float waterTemp;
    float airTemp; 
    long aveWaterTemp;
    long aveAirTemp;

    TempSensor();
    void getTemperatures();
};

#endif