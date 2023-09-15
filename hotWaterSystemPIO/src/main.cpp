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
int lastMode = 3;
int waterTempThresh = 24;
int airTempThresh = 24;
float waterTemp = 0;
float airTemp = 0;
int menuItem = 1;
int waterLevel = 100;
bool edit = false;
int fillCommand = 0;
int pos = 0;    // servo starting position
int previousMillis = 0;
int interval = 50;

unsigned long Ts = 3000; // temperature sampling time
unsigned long lastMeasurementTime = 0;

RotEncoder encoder(CLK, DT, SW);
PowerButton OnButton(ONBUT);
TempSensor tempSensors;
Display display;
Relay pumpRelay(PUMPPIN);
Diverter diverter;

void setup() {
  Serial.begin(9600); 
  display.init();
  diverter.begin(SERVOPIN);
}


void loop() {

  diverter.update();

  if (millis() - lastMeasurementTime > Ts) {
    lastMeasurementTime = millis();
    tempSensors.getTemperatures();

    // Serial.print("Water Temp: ");
    // Serial.println(tempSensors.waterTemp);
    // Serial.print("Air Temp: ");
    // Serial.println(tempSensors.airTemp);

    //display.updateDisplay(tempSensors.waterTemp, waterTempThresh, tempSensors.airTemp, airTempThresh, menuItem, edit, mode);
  }
  //Serial.println(edit);


  //display.updateDisplay(tempSensors.waterTemp, waterTempThresh, tempSensors.airTemp, airTempThresh, 1, 1, mode);

  ////////////////////////////////////////////////////////////////////////////
  // modes: [0] off, [1] on, [2] fill

  // case [0]: pump off, diverter position 1 (hot air), ball valve closed
  // case [1]: pump off/on, diverter position 2 (hot water), ball valve closed
  // case [2]: pump off, diveter position (hot air), ball valve open
  /////////////////////////////////////////////////////////////////////////

  OnButton.readButton();
 
  if (OnButton.buttonState != OnButton.lastButtonState) {
    lastMode = mode;
    //Serial.println(OnButton.buttonState);
    OnButton.lastButtonState = OnButton.buttonState;
    if (OnButton.buttonState == 0) {
      mode = 0;
    }
    else {
      mode = 1;
      fillCommand = 0;
    }
  }


  /////////////////// Obtain Encoder Reading ////////////////////////


  // menuItem += 1;


  encoder.readEncoder();


  if (encoder.btnPress == true) {
    encoder.btnPress = false;
    if (edit == false) { 
      edit = true;
    }
    else {
      edit = false;
    }

    //UNCOMMENT FOR DEBUGGING
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
    //menuItem=1;
    //display.updateDisplay(tempSensors.waterTemp, waterTempThresh, tempSensors.airTemp, airTempThresh, menuItem, edit, mode);
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
      // case 3:
      //   if (OnButton.buttonState == 0) {
      //     // fillCommand = fillCommand + encoder.val;
      //     // if (fillCommand >= 1) {
      //     //   fillCommand = 1;
      //     //   display.setFilling(1);
      //     //   mode = 2;
      //     // }
      //     // else if (fillCommand <= 0) {
      //     //   fillCommand = 0;
      //     //   display.setFilling(0);
      //     //   mode = 0;
      //     // }
      //     fillCommand = 1;
      //     display.setFilling(1);
      //     mode = 2;
      //   }
      default:
        break;
      }
    } 

    //UNCOMMENT FOR DEBUGGING
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
    //menuItem=1;
    //display.updateDisplay(tempSensors.waterTemp, waterTempThresh, tempSensors.airTemp, airTempThresh, menuItem, edit, mode);
  }

    if (OnButton.buttonState == 0 && menuItem == 3 && edit == true) {
    // fillCommand = fillCommand + encoder.val;
    // if (fillCommand >= 1) {
    //   fillCommand = 1;
    //   display.setFilling(1);
    //   mode = 2;
    // }
    // else if (fillCommand <= 0) {
    //   fillCommand = 0;
    //   display.setFilling(0);
    //   mode = 0;
    // }
    //fillCommand = 1;
    display.setFilling(1);
    mode = 2;
  }
  else if (menuItem == 3) {
    //fillCommand = 0;
    display.setFilling(0);
    mode = 0;
  }

  if (mode != lastMode && mode == 0) {
    pumpRelay.triggerOff();
    diverter.close();
    //fillValve.close();
    lastMode = mode;
  }

  //Serial.println(mode);

  switch (mode) {
    case 1:
      if (tempSensors.airTemp > airTempThresh) {
        pumpRelay.triggerOn();
      }
      else if (tempSensors.airTemp < airTempThresh) {
        pumpRelay.triggerOff();
      }
      if (tempSensors.waterTemp < waterTempThresh) {
        diverter.open();
     }
      else if (tempSensors.waterTemp> waterTempThresh) {
        diverter.close();
      }
      //fillValve.close();
    break;
    case 2:
      pumpRelay.triggerOff();
      diverter.close();
        if (waterLevel > 100) { 
          //fillValve.close();
        }
        else if (waterLevel < 100)
          //fillValve.open();
    break;
  }
}