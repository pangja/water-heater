#include <Arduino.h>
#include <TempSensor.h>
#include <Diverter.h>
#include <LevelSensor.h>
#include <PowerButton.h>
#include <Relay.h>

int mode = 0;
int lastMode = 0;
int waterTempThresh = 60;
int airTempThresh = 50;
int waterTemp;
int airTemp;

void setup() {
  // put your setup code here, to run once:
  // initialise display

}

void loop() {
  ////////////////////////////////////////////////////////////////////////////
  // modes: [1] off, [2] on, [3] cooldown, [4] fill 

  // case [1]: pump off, diverter position 1 (hot air), ball valve closed
  // case [2]: pump off/on, diverter position 2 (hot water), ball valve closed
  // case [3]: pump on, diverter position 1, ball valve closed
  // case [4]: pump off, diveter position (hot air), ball valve open
  ///////////////////////////////////////////////////////////////////////////
  if (mode != lastMode) {
    switch (mode) {
      case 1:
        break;
      case 2:
        break;
      case 3;
        break;
      case 4
        break;
    }
  }

}