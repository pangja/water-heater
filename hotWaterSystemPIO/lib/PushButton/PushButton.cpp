#include "PushButton.h"

PushButton::PushButton(int buttonPin)
{
    pin = buttonPin;
    pinMode(pin, INPUT);
}

bool PushButton::readButton()
{  
  buttonState = digitalRead(pin);

  //filter noise (debounce)
  if ( (millis() - lastDebounceTime) > debounceDelay && buttonState == HIGH) {
    state = true;
    lastDebounceTime = millis(); //set the current time
  }
  else {
    state = false;
  }
}
