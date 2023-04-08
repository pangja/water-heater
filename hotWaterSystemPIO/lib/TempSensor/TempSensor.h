#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
#include "Arduino.h"

class TempSensor
{
private:
    int pin;
    int temp;
    int aveTemp;

public:
    TempSensor(int sensorPin);

    int readTemp();
};

#endif