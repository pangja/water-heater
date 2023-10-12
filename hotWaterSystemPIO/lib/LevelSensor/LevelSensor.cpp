#include "LevelSensor.h"

LevelSensor::LevelSensor(uint8_t levelPin)
{
    pin = levelPin;
}

void LevelSensor::readLevel()
{  
  level = analogRead(pin);
  if (level >= 50) {
    full = true;
  } else {
    full = false;
  }
}
