#ifndef DIVERTER_H
#define DIVERTER_H
#include "Arduino.h"
#include "Servo.h"

class Diverter
{
private:
    uint16_t target = 90;       // target angle
    uint16_t current = 90;      // current angle
    uint8_t interval = 20;      // delay time
    uint32_t previousMillis = 0;

public:
    Servo servo;

    void begin(int pin);
    void setSpeed(uint8_t newSpeed);
    void set(uint16_t newTarget);
    void update();
};

#endif