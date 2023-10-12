#ifndef POWERBUTTON_H
#define POWERBUTTON_H
#include "Arduino.h"

class PowerButton
{
private:
    uint8_t pin;
public:
    uint8_t buttonState;
    uint8_t lastButtonState;

    PowerButton(uint8_t buttonPin);
    uint8_t readButton();
};

#endif