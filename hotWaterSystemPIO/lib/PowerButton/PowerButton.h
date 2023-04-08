#ifndef POWERBUTTON_H
#define POWERBUTTON_H
#include "Arduino.h"

class PowerButton
{
private:
    int pin;
public:
    int buttonState;

    PowerButton(int buttonPin);
    int readButton();
};

#endif