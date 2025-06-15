#include "Display.h"

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setupDisplay() {
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.backlight();
  lcd.clear();
}

void showMessage(const String& line1, const String& line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void displayReadings(float ph, float temp, float humidity, float moisture, String moistureStatus) {
  lcd.clear();

  //Line 1: pH and Temperature with °C
  lcd.setCursor(0, 0);
  lcd.print("pH:");
  lcd.print(ph, 1);
  lcd.print(" T:");
  lcd.print(temp, 1);
  lcd.print((char)223);
  lcd.print("C");

  //Line 2: Humidity with % and Moisture
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity, 0);
  lcd.print("% M:");

  String moistureStr = String((int)moisture) + "%(" + moistureStatus+")";
  lcd.print(moistureStr);
}
