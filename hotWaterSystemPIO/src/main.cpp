#include <Arduino.h>
#include <TempSensor.h>
#include <Diverter.h>
#include <LevelSensor.h>
#include <PowerButton.h>
#include <Relay.h>
#include <RotEncoder.h>
#include <Pins.h>
#include <TempSensor.h>
#include <Display.h>
#include <LevelSensor.h>

  ////////////////////////////////////////////////////////////////////////////
  // modes: [0] off, [1] on, [2] fill

  // case [0]: pump off, diverter position 1 (hot air), ball valve closed
  // case [1]: pump off/on, diverter position 2 (hot water), ball valve closed
  // case [2]: pump off, diveter position (hot air), ball valve open
  /////////////////////////////////////////////////////////////////////////

int8_t mode = 0;
uint8_t waterTempThresh = 35;
uint8_t airTempThresh = 40;
float waterTemp = 0;
float airTemp = 0;
int8_t menuItem = 1;
bool edit = false;
int8_t fillCommand = 0;
int16_t pos = 0;    // servo starting position
bool updateMode = false;

unsigned long Ts = 3000; // temperature sampling time
unsigned long lastMeasurementTime = 0;

RotEncoder encoder(CLK, DT, SW);
PowerButton OnButton(ONBUT);
TempSensor tempSensors;
Display display;
Relay pumpRelay(PUMPPIN);
Relay valveRelay(VALVEPIN);
Diverter diverter;
LevelSensor levelSensor(LEVELPIN);

void setup() {
  Serial.begin(9600); 
  display.init();
  diverter.begin(SERVOPIN);
  diverter.close();
}

void loop() {

  diverter.update();

  // Read temp every Ts seconds and update display
  if (millis() - lastMeasurementTime > Ts) {
    lastMeasurementTime = millis();
    tempSensors.getTemperatures();
    display.updateDisplay(tempSensors.waterTemp, waterTempThresh, tempSensors.airTemp, airTempThresh, menuItem, edit, mode);
  }

  // Update mode if switch switched
  OnButton.readButton();
  if (OnButton.buttonState != OnButton.lastButtonState) {
    updateMode = true;
    OnButton.lastButtonState = OnButton.buttonState;
    if (OnButton.buttonState == 0) {
      mode = 0;
    }
    else {
      mode = 1;
      fillCommand = 0;
    }
  }

  encoder.readEncoder();

  // Set edit mode if button pressed
  if (encoder.btnPress == true && !(menuItem == 3 && OnButton.buttonState == 1)) {
    encoder.btnPress = false;
    if (edit == false) { 
      edit = true;
    }
    else {
      edit = false;
    }
    display.updateDisplay(tempSensors.waterTemp, waterTempThresh, tempSensors.airTemp, airTempThresh, menuItem, edit, mode);
  }

  // Switch menu item when encoder is rotated
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
      switch (menuItem){
        case 1:   // WATER TEMP
          waterTempThresh = waterTempThresh + encoder.val;
          if (waterTempThresh > 80) {
            waterTempThresh = 80;
          }
          else if (waterTempThresh < 20) {
            waterTempThresh = 20;
          }
          break;
        case 2:   // AIR TEMP
          airTempThresh = airTempThresh + encoder.val;
          if (airTempThresh > 80) {
            airTempThresh = 80;
          }
          else if (airTempThresh < 20) {
            airTempThresh = 20;
          }
        default:
          break;
      }
    } 

    display.updateDisplay(tempSensors.waterTemp, waterTempThresh, tempSensors.airTemp, airTempThresh, menuItem, edit, mode);
  }

  // Toggle fill mode 
  if (menuItem == 3){
    if (edit == true && OnButton.buttonState == 0) {
      display.setFilling(1);
      mode = 2;
      updateMode = true;
    }else{
      display.setFilling(0);
      if (OnButton.buttonState == 0){
        mode = 0;
      }else {
        mode = 1;
      }
      updateMode = true;
    }
  }

  switch (mode) {
    case 0:   // OFF (when power switch is off)
      if (updateMode) {
        pumpRelay.triggerOff();
        diverter.close();
        valveRelay.triggerOff();
        updateMode = false;
      }
      break;
    case 1:   // ON
      valveRelay.triggerOff();
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
      break;
    case 2:   // OFF AND FILL
        valveRelay.triggerOn();
        levelSensor.readLevel();
        if (levelSensor.full){ // CLOSES VALVE IF TANK TANK IS FULL
          edit = false;
        }
      break;
  }
}