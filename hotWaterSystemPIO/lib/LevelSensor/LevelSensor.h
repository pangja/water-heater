#ifndef LEVELSENSOR_H
#define LEVELSENSOR_H
#include "Arduino.h"

class LevelSensor
{
private:
    int pin;
    int level;
public:
    LevelSensor(int levelPin);
    void readLevel();
    bool full;
};

#endif