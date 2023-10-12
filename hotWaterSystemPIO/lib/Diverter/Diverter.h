#ifndef DIVERTER_H
#define DIVERTER_H
#include "Arduino.h"
#include "Servo.h"

class Diverter
{
private:
    int16_t target; //= 90;       // target angle
    int16_t current; //= 90;      // current angle
    unsigned long interval = 20;      // delay time
    unsigned long previousMillis = 0;

public:
    Servo servo;

    void begin(uint8_t pin);
    void setSpeed(unsigned long newSpeed);
    void open();
    void close();
    void update();
};

#endif