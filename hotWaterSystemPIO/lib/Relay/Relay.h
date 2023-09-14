#ifndef RELAY_H
#define RELAY_H
#include "Arduino.h"

class Relay
{
private:
    int pin;
public:
    int state;

    Relay(int relayPin);
    void triggerOn();
    void triggerOff();
};

#endif