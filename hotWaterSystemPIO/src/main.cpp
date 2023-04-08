#include <Arduino.h>
#include <TempSensor.h>

int mode = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  
  // modes: [1] off, [2] on, [3] cooldown, [4] fill 

  // case [1]: pump off, diverter position 1 (hot air), ball valve closed
  // case [2]: pump off/on, diverter position 2 (hot water), ball valve closed
  // case [3]: pump on, diverter position 1, ball valve closed
  // case [4]: pump off, diveter position (hot air), ball valve open
}