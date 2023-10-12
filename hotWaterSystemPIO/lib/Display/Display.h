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
    bool flash = false;
    bool filling = false;
    uint8_t i = 0;
    unsigned long lastDisplayTime;
    unsigned long lastFillTime;

public:
    int menu;
    Display();
    void init();
    void updateDisplay(float waterTemp, uint8_t setWaterTemp, float airTemp, uint8_t setAirTemp, int8_t menuItem, bool edit, int8_t mode);
    void displayWater(float waterTemp, uint8_t setWaterTemp, bool edit);
    void displayAir(float airTemp, uint8_t setAirTemp, bool edit);
    void displayFill(int8_t mode);
    void setFilling(bool fillCommand);
};

#endif