#include "PowerButton.h"

PowerButton::PowerButton(int buttonPin){
    pin = buttonPin;
    pinMode(pin, INPUT);
}

int PowerButton::readButton(){
    buttonState = digitalRead(pin);
}