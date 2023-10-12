#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H
#include "Arduino.h"

class PushButton
{
private:
    int pin;
    int buttonState;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
public:
    bool state;

    PushButton(int buttonPin);
    bool readButton();
};

#endif