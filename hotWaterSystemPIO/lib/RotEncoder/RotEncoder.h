#ifndef ROTENCODER_H
#define ROTENCODER_H
#include "Arduino.h"

class RotEncoder
{
private:
    uint8_t clk;
    uint8_t dt;
    uint8_t sw;
    uint8_t currentStateCLK;
    uint8_t lastStateCLK;
    unsigned long lastButtonPress = 0;
    uint8_t btnState;

public:
    bool rotation = false;
    bool btnPress = false;
    int8_t val;
    RotEncoder(uint8_t clk, uint8_t dt, uint8_t sw);
    void readEncoder();
};

#endif