#include "TempSensor.h"

TempSensor::TempSensor(int sensorPin)
{
    dataPin=sensorPin;
}

// Date member function
int TempSensor::readTemp()
{
    //int rawValue = analogueread(dataPin)
    // return temp = processed value
}
