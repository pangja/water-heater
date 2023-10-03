#include "LevelSensor.h"

LevelSensor::LevelSensor(int levelPin)
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
