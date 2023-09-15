#include "Diverter.h"

void Diverter::begin(int pin)
{
    servo.attach(pin);
}

void Diverter::setSpeed(uint8_t newSpeed)
{
    interval = newSpeed;
}

void Diverter::close()
{
    target = 0;
}

void Diverter::open(){
    target = 90;
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




