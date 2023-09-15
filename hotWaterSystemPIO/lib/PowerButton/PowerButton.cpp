#include "PowerButton.h"

PowerButton::PowerButton(int buttonPin){
    pin = buttonPin;
    pinMode(pin, INPUT);
    buttonState = 0;
    lastButtonState = 2;
}

int PowerButton::readButton(){
    buttonState = digitalRead(pin);
}