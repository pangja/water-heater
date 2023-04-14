#include <Arduino.h>
#include <TempSensor.h>
#include <Diverter.h>
#include <LevelSensor.h>
#include <PowerButton.h>
#include <PushButton.h>
#include <Relay.h>
#include <RotEncoder.h>
#include <Pins.h>
#include <TempSensor.h>
#include <Display.h>

int mode = 0;
int lastMode = 0;
int waterTempThresh = 60;
int airTempThresh = 50;
int waterTemp = 0;
int airTemp = 0;
int menuItem = 1;
int waterLevel = 100;
bool edit = 0;
int fillCommand = 0;

unsigned long Ts = 1000; // temperature sampling time
unsigned long lastMeasurementTime = 0;

RotEncoder encoder(CLK, DT, SW);
PowerButton OnButton(ONBUT);
TempSensor tempSensors;
Display display;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //For debugging
  display.init();
}

void loop() {

  if (millis() - lastMeasurementTime > Ts) {
    lastMeasurementTime = millis();
    tempSensors.getTemperatures();
    Serial.print("Water Temp: ");
    Serial.println(tempSensors.waterTemp);
    Serial.print("Air Temp: ");
    Serial.println(tempSensors.airTemp);
  }


  ////////////////////////////////////////////////////////////////////////////
  // modes: [0] off, [1] on, [2] fill

  // case [0]: pump off, diverter position 1 (hot air), ball valve closed
  // case [1]: pump off/on, diverter position 2 (hot water), ball valve closed
  // case [2]: pump off, diveter position (hot air), ball valve open
  ///////////////////////////////////////////////////////////////////////////

  OnButton.readButton();
  if (OnButton.buttonState != OnButton.lastButtonState) {
    OnButton.lastButtonState = OnButton.buttonState;
    if (OnButton.buttonState == 0) {
      mode = 0;
    }
    else {
      mode = 1;
      fillCommand = 0;
    }
  }

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
        if (OnButton.buttonState == 0) {
          fillCommand = fillCommand + encoder.val;
          if (fillCommand >= 1) {
            fillCommand = 1;
            mode = 2;
          }
          else if (fillCommand <= 0) {
            fillCommand = 0;
            mode = 0;
          }
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


  //display.updateDisplay(tempSensors.waterTemp, waterTempThresh, tempSensors.airTemp, airTempThresh,  menuItem, edit, mode);


  // if (mode != lastMode) {
  //   lastMode = mode;
  //   switch (mode) {
  //     case 0:
  //     pump.off();
  //     diverter.close();
  //     fillValve.close();
  //       break;
  //     case 1:
  //     if (airTemp > airTempThresh) {
  //       pump.on();
  //     }
  //     else if (airTemp < airTempThresh) {
  //       pump.off();
  //     }
  //     if (waterTemp < waterTempThresh) {
  //       diverter.open();
  //     }
  //     else if (waterTemp > waterTempThresh) {
  //       diverter.close();
  //     }
  //     fillValve.close();
  //       break;
  //     case 2:
  //     pump.off();
  //     diverter.close();
  //     if (waterLevel > 100) { // NNED TO RECHECK THIS STATEMENT
  //       fillValve.close();
  //     }
  //     else if (waterLevel < 100)
  //       fillValve.open();
  //       break;
  //   }
  // }
}