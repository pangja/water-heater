#include "Display.h"

Display::Display() {
}

void Display::setFilling(bool fillCommand) {
  filling = fillCommand;
}

void Display::init() {
  lastDisplayTime = millis();
  lastFillTime = millis();
  delay(250); // wait for the OLED to power up
  oled.begin(i2c_Address, true); // Address 0x3C default
}

void Display::updateDisplay(float waterTemp, uint8_t setWaterTemp, float airTemp, uint8_t setAirTemp, int8_t menuItem, bool edit, int8_t mode) {

    if(menuItem == 1){
      displayWater(waterTemp, setWaterTemp, edit);
    }else if(menuItem == 2){
      displayAir(airTemp, setAirTemp, edit);
    }else if(menuItem == 3){
      displayFill(mode);
    }

    oled.display();

}

void Display::displayWater(float waterTemp, uint8_t setWaterTemp, bool edit){
  oled.clearDisplay();
  oled.drawLine(0, 10, 128, 10, SH110X_WHITE);
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);
  //const char* waterTitle = "WATER TEMPERATURE";
  oled.print(F("WATER TEMPERATURE"));
  oled.setTextSize(2);

  if (edit == false) {
    oled.setCursor(0, 18);
    oled.print(F("TEMP:"));
    oled.print(waterTemp);
    oled.setCursor(0, 40);
    oled.print(F("SET:"));
    oled.print(setWaterTemp);
  }
  else {
    oled.setCursor(0, 18);
    oled.print(F("TEMP:"));
    oled.print(waterTemp);
    oled.setCursor(0, 40);
    oled.print(F("SET:"));

    if (millis() - lastDisplayTime > 100) {
      if (flash == 0) {
        flash = 1;
      } else {
        {
          flash = 0;
        }
      }
      lastDisplayTime = millis();
    }
    if (flash == 0) {
      oled.print(setWaterTemp);
    }
  }

}

void Display::displayAir(float airTemp,  uint8_t setAirTemp, bool edit){
  oled.clearDisplay();
  oled.drawLine(0, 10, 128, 10, SH110X_WHITE);
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);
  //const char* airTitle = "AIR TEMPERATURE";
  oled.print(F("AIR TEMPERATURE"));
  // oled.print("AIR TEMPERATURE");
  oled.setTextSize(2);

  if (edit == false) {
    oled.setCursor(0, 18);
    oled.print(F("TEMP:"));
    oled.print(airTemp);
    oled.setCursor(0, 40);
    oled.print(F("SET:"));
    oled.print(setAirTemp);
  }
  else {
    oled.setCursor(0, 18);
    oled.print(F("TEMP:"));
    oled.print(airTemp);
    oled.setCursor(0, 40);
    oled.print(F("SET:"));
    if (millis() - lastDisplayTime > 500) {
      if (flash == 0) {
        flash = 1;
      } else {
        {
          flash = 0;
        }
      }
      lastDisplayTime = millis();
    }
    if (flash == 0) {
      oled.print(setAirTemp);
    } else {
      oled.print("");
    }
  }
}

void Display::displayFill(int8_t mode){
  oled.clearDisplay();
  oled.drawLine(0, 10, 128, 10, SH110X_WHITE);
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);
  oled.print(F("FILL SETTINGS"));
  oled.setTextSize(2);
  oled.setCursor(0, 30);
  
  if (filling == false) {
    oled.setCursor(15, 18);
    oled.print(F("PRESS TO"));
    oled.setCursor(40, 40);
    oled.print(F("FILL"));
  }
  else {
    if (millis()-lastFillTime > 100) {
      if (i < 3) {
        i++;
      } else {
        i = 0;
      }  
      lastFillTime = millis();
    }
    if (i == 0) {
      oled.print(F("FILLING"));
    } else if (i == 1) {
      oled.print(F("FILLING."));
    } else if (i == 2) {
      oled.print(F("FILLING.."));
    } else {
      oled.print(F("FILLING..."));
    }
  }

}