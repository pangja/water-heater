#include "Diverter.h"

void Diverter::begin(uint8_t pin)
{
    servo.attach(pin);
}

void Diverter::setSpeed(unsigned long newSpeed)
{
    interval = newSpeed;
}

void Diverter::close()
{
    target = 5;
}

void Diverter::open(){
    target = 180;
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




