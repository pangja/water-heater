#include "Relay.h"

Relay::Relay(int relayPin){
    pin = relayPin;
    pinMode(pin, OUTPUT);
}

void Relay::triggerOn(){
    digitalWrite(pin, HIGH);
}

void Relay::triggerOff(){
    digitalWrite(pin, LOW);
}