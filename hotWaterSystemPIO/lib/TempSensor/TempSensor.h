#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

class TempSensor
{
private:
    int dataPin;
    int temp;
    int aveTemp;

public:
    TempSensor(int sensorPin);

    int readTemp();
};

#endif