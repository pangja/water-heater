#include "Diverter.h"

void Diverter::begin(int pin)
{
    servo.attach(pin);
}

void Diverter::setSpeed(uint8_t newSpeed)
{
    interval = newSpeed;
}

void Diverter::set(uint16_t newTarget)
{
    target = newTarget;
}

void Diverter::update() 
{
    if (millis() - previousMillis > interval)
       {
        previousMillis = millis();
        if (target < current)
        {
          current--;
          servo.write(current);
        }
        else if (target > current)
        {
          current++;
          servo.write(current);
        }
      }
}




