#include "Display.h"

Display::Display() {
}

void Display::init() {
  //Serial.begin(9600);
  lastDisplayTime = millis();
  lastFillTime = millis();
  delay(250); // wait for the OLED to power up
  oled.begin(i2c_Address, true); // Address 0x3C default
}

void Display::updateDisplay(float waterTemp, int setWaterTemp, float airTemp, int setAirTemp, int menuItem, bool edit, int mode) {
    // switch (menuItem) {
    //     case 1:
    //     displayWater(waterTemp, setWaterTemp);
    //     break;
    //     case 2:
    //     displayAir(airTemp, setAirTemp);
    //     break;
    //     case 3:
    //     displayFill(mode);
    // }
    displayWater(waterTemp, setWaterTemp);
    oled.display();
}

void Display::displayWater(long waterTemp, long setWaterTemp){
  oled.clearDisplay();
  oled.drawLine(0, 10, 128, 10, SH110X_WHITE);
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);
  oled.print("WATER TEMPERATURE");
  oled.setTextSize(2);

  if (edit == false) {
    oled.setCursor(0, 18);
    oled.print("TEMP:");
    oled.print(waterTemp);
    oled.setCursor(0, 40);
    oled.print("SET:");
    oled.print(setWaterTemp);
  }
  else {
    oled.setCursor(0, 18);
    oled.print("TEMP:");
    oled.print(32);
    oled.setCursor(0, 40);
    oled.print("SET:");

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
      oled.print(60);
    }
  }

}

void Display::displayAir(long airTemp, long setAirTemp){
  oled.clearDisplay();
  oled.drawLine(0, 10, 128, 10, SH110X_WHITE);
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);
  oled.print("AIR TEMPERATURE");
  oled.setTextSize(2);

  if (edit == false) {
    oled.setCursor(0, 18);
    oled.print("TEMP:");
    oled.print(32);
    oled.setCursor(0, 40);
    oled.print("SET:");
    oled.print(60);
  }
  else {
    oled.setCursor(0, 18);
    oled.print("TEMP:");
    oled.print(32);
    oled.setCursor(0, 40);
    oled.print("SET:");
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
      oled.print(60);
    }
  }
}

void Display::displayFill(int mode){
  oled.clearDisplay();
  oled.drawLine(0, 10, 128, 10, SH110X_WHITE);
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);
  oled.print("FILL SETTINGS");
  oled.setTextSize(2);
  oled.setCursor(0, 30);
  
  if (filling == false) {
    oled.setCursor(15, 18);
    oled.print("PRESS TO");
    oled.setCursor(40, 40);
    oled.print("FILL");
  }
  else {
    if (millis()-lastFillTime > 300) {
      if (i < 4) {
        i++;
      } else {
        i = 0;
      }  
      lastFillTime = millis();
    }
    if (i == 0) {
      oled.print("FILLING");
    } else if (i == 1) {
      oled.print("FILLING.");
    } else if (i == 2) {
      oled.print("FILLING..");
    } else {
      oled.print("FILLING...");
    }
  }

}