#include "Display.h"

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setupDisplay() {
  Wire.begin(I2C_SDA, I2C_SCL); // Start I2C on specified ESP32 pins
  delay(50);                    // Small delay to stabilize LCD power
  lcd.init();                   // Initialize LCD (ESP32-friendly)
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

void displayReadings(const SensorData& data) {
  lcd.clear();

  // Line 1: Display pH and Temperature with °C symbol
  lcd.setCursor(0, 0);
  lcd.print("pH:");
  lcd.print(data.ph, 1);
  lcd.print(" T:");
  lcd.print(data.temperature, 1);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");

  // Line 2: Display Humidity and Moisture with status
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(data.humidity, 0);
  lcd.print("% M:");

  String moistureStr = String((int)data.moisture) + "%(" + data.moistureStatus + ")";
  lcd.print(moistureStr);
}
