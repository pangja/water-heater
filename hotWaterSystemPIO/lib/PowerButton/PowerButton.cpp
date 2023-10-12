#include "PowerButton.h"

PowerButton::PowerButton(uint8_t buttonPin){
    pin = buttonPin;
    pinMode(pin, INPUT);
    buttonState = 0;
    lastButtonState = 2;
}

uint8_t PowerButton::readButton(){
    buttonState = digitalRead(pin);
}