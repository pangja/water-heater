#include "Relay.h"

Relay::Relay(uint8_t relayPin){
    pin = relayPin;
    pinMode(pin, OUTPUT);
}

void Relay::triggerOn(){
    digitalWrite(pin, HIGH);
}

void Relay::triggerOff(){
    digitalWrite(pin, LOW);
}