#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Configuration
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

// I2C pins for ESP32 (SDA = 21, SCL = 22)
#define I2C_SDA 21
#define I2C_SCL 22

extern LiquidCrystal_I2C lcd; //declaration only

void setupDisplay();
void showMessage(const String& line1, const String& line2 = "");
void displayReadings(float ph, float temp, float humidity, float moisture, String moistureStatus);

#endif
