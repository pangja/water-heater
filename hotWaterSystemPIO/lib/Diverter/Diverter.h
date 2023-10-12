#ifndef DIVERTER_H
#define DIVERTER_H
#include "Arduino.h"
#include "Servo.h"

class Diverter
{
private:
    int target; //= 90;       // target angle
    int current; //= 90;      // current angle
    unsigned long interval = 20;      // delay time
    unsigned long previousMillis = 0;

public:
    Servo servo;

    void begin(int pin);
    void setSpeed(int newSpeed);
    void open();
    void close();
    void update();
};

#endif