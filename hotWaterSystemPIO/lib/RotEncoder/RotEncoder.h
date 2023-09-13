#ifndef ROTENCODER_H
#define ROTENCODER_H
#include "Arduino.h"

class RotEncoder
{
private:
    int clk;
    int dt;
    int sw;
    int currentStateCLK;
    int lastStateCLK;
    unsigned long lastButtonPress = 0;
    int btnState;

public:
    bool rotation = false;
    bool btnPress = false;
    int val;
    RotEncoder(int clk, int dt, int sw);
    void readEncoder();
};

#endif