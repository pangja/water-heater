#ifndef ROTENCODER_H
#define ROTENCODER_H
#include "Arduino.h"

class RotEncoder
{
private:
    int clk;
    int dt;
    long lastDebounceTime = 0;
    int debounceDelay = 50;
    int currentStateCLK;
    int lastStateCLK;

public:
    String currentDir = "";
    bool rotation = false;
    int val;
    int counter;
    RotEncoder(int clk, int dt);
    void readEncoder();
};

#endif