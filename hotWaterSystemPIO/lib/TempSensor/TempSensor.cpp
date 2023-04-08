#include "TempSensor.h"

TempSensor::TempSensor(int sensorPin)
{
    pin = sensorPin;
    pinMode(pin, INPUT);
}

// Date member function
int TempSensor::readTemp()
{
    int rawValue = digitalRead(pin);
    return temp = rawValue; // PROCESS RAW VALUE
}
