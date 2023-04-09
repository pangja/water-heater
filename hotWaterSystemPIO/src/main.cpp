#include <Arduino.h>
#include <TempSensor.h>
#include <Diverter.h>
#include <LevelSensor.h>
#include <PowerButton.h>
#include <PushButton.h>
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
bool edit = 0;
int fillCommand = 0;

RotEncoder encoder(CLK, DT, SW);

void setup() {
  // put your setup code here, to run once:
  // initialise display
  Serial.begin(9600); //For debugging
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

  ///////////////////// Obtain Encoder Reading ////////////////////////

  encoder.readEncoder();
  if (encoder.btnPress == true) {
    if (edit == false) {
      edit = true;
    }
    else {
      edit = false;
    }

    // UNCOMMENT FOR DEBUGGING
    // encoder.btnPress = false;
    // Serial.print("Menu Item: ");
		// Serial.print(menuItem);
    // Serial.print(" | WaterTemp thresh:");
    // Serial.print(waterTempThresh);
    // Serial.print(" | AirTemp thresh:");
    // Serial.print(airTempThresh);
    // Serial.print(" | fillCommand");
    // Serial.print(fillCommand);
		// Serial.print(" | edit: ");
		// Serial.println(edit);
  }

  if (encoder.rotation == true) {
    encoder.rotation = false;
    if (edit == false) {
      menuItem = menuItem + encoder.val;
      if (menuItem > 3) {
        menuItem = 3;
      }
      else if (menuItem < 1) {
        menuItem = 1;
      }
    }

    if (edit == true){
      switch (menuItem)
      {
      case 1:
        waterTempThresh = waterTempThresh + encoder.val;
        if (waterTempThresh > 80) {
          waterTempThresh = 80;
        }
        else if (waterTempThresh < 20) {
          waterTempThresh = 20;
        }
        break;
      case 2:
        airTempThresh = airTempThresh + encoder.val;
        if (airTempThresh > 80) {
          airTempThresh = 80;
        }
        else if (airTempThresh < 20) {
          airTempThresh = 20;
        }
      case 3:
        fillCommand = fillCommand + encoder.val;
        if (fillCommand > 1) {
          fillCommand= 1;
        }
        else if (fillCommand < 0) {
          fillCommand = 0;
        }
      default:
        break;
      }
    }
    // UNCOMMENT FOR DEBUGGING
    // Serial.print("Menu Item: ");
		// Serial.print(menuItem);
    // Serial.print(" | WaterTemp thresh:");
    // Serial.print(waterTempThresh);
    // Serial.print(" | AirTemp thresh:");
    // Serial.print(airTempThresh);
    // Serial.print(" | fillCommand:");
    // Serial.print(fillCommand);
		// Serial.print(" | edit: ");
		// Serial.println(edit);
  }
}