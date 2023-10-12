#ifndef LEVELSENSOR_H
#define LEVELSENSOR_H
#include "Arduino.h"

class LevelSensor
{
private:
    uint8_t pin;
    uint8_t level;
public:
    LevelSensor(uint8_t levelPin);
    void readLevel();
    bool full;
};

#endif