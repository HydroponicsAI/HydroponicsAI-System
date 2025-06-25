#include "Display.h"

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setupDisplay() {
  Wire.begin(I2C_SDA, I2C_SCL);  // Start I2C on specified ESP32 pins
  delay(50);                     // Small delay to stabilize LCD power
  lcd.init();                    // Initialize LCD (ESP32-friendly)
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
  static unsigned long lastDisplaySwitch = 0;
  static int currentPage = 0;
  static const unsigned long displayInterval = 2000;  // 3 seconds per page

  unsigned long now = millis();

  if (now - lastDisplaySwitch >= displayInterval) {
    lastDisplaySwitch = now;
    currentPage = (currentPage + 1) % 2;  // 0 → 1  → 0 ...
    lcd.clear();

    switch (currentPage) {
      case 0:
        // Page 1: Temp, pH, Humidity, Moisture with status
        lcd.setCursor(0, 0);
        lcd.print("T:");
        lcd.print(data.temperature, 1);
        lcd.print((char)223);
        lcd.print("C pH:");
        lcd.print(data.ph, 1);

        lcd.setCursor(0, 1);
        lcd.print("H:");
        lcd.print(data.humidity, 0);
        lcd.print("% M:");
        lcd.print(data.moisture);
        lcd.print("%(");
        lcd.print(data.moistureStatus);
        lcd.print(")");
        break;

      case 1:
        // Page 2: NPK values with unit after each
        lcd.setCursor(0, 0);
        lcd.print("In (mg/Kg): ");
        lcd.setCursor(0, 1);
        lcd.print("N: ");
        lcd.print(data.nitrogen);
        lcd.print(" P:");
        lcd.print(data.phosphorous);
        lcd.print(" K:");
        lcd.print(data.potassium);
        break;
    }
  }
}
