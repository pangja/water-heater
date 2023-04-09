#include <Arduino.h>
#include <TempSensor.h>
#include <Diverter.h>
#include <LevelSensor.h>
#include <PowerButton.h>
#include <Relay.h>
#include <RotEncoder.h>
#include <Pins.h>

int mode = 0;
int lastMode = 0;
int waterTempThresh = 60;
int airTempThresh = 50;
int waterTemp;
int airTemp;
int menuItem = 1;

RotEncoder encoder(CLK, DT);

void setup() {
  // put your setup code here, to run once:
  // initialise display
  Serial.begin(9600);
}

void loop() {
  ////////////////////////////////////////////////////////////////////////////
  // modes: [1] off, [2] on, [3] cooldown, [4] fill 

  // case [1]: pump off, diverter position 1 (hot air), ball valve closed
  // case [2]: pump off/on, diverter position 2 (hot water), ball valve closed
  // case [3]: pump on, diverter position 1, ball valve closed
  // case [4]: pump off, diveter position (hot air), ball valve open
  ///////////////////////////////////////////////////////////////////////////
  // if (mode != lastMode) {
  //   switch (mode) {
  //     case 1:
  //       break;
  //     case 2:
  //       break;
  //     case 3;
  //       break;
  //     case 4
  //       break;
  //   }
  // }
  encoder.readEncoder();
  if (encoder.rotation == true) {
    encoder.rotation = false;
    menuItem = menuItem + encoder.val;
    if (menuItem > 3) {
      menuItem = 3;
    }
    else if (menuItem < 1) {
      menuItem = 1;
    }
    Serial.println(menuItem); // Debugging
  }
}