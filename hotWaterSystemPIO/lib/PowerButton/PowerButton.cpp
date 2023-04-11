#include "PowerButton.h"

PowerButton::PowerButton(int buttonPin){
    pin = buttonPin;
    pinMode(pin, INPUT);
    lastButtonState = digitalRead(pin);
}

int PowerButton::readButton(){
    buttonState = digitalRead(pin);
}