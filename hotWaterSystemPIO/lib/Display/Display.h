#ifndef DISPLAY_H
#define DISPLAY_H

#include "arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SH110X.h"

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
//Adafruit_SH1106G oled = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

class Display
{
private:
    Adafruit_SH1106G oled = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 
    bool edit;
    bool flash = false;
    bool filling = false;
    int i = 0;
    long lastDisplayTime;
    long lastFillTime;

public:
    Display();
    void init();
    void updateDisplay(long waterTemp, long setWaterTemp, long airTemp, long setAirTemp, int menuItem, bool edit, int mode);
    void displayWater(long waterTemp, long setWaterTemp);
    void displayAir(long airTemp, long setAirTemp);
    void displayFill(int mode);
};

#endif