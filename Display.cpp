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
  static const unsigned long displayInterval = 3000;  // 3 seconds per page

  unsigned long now = millis();

  if (now - lastDisplaySwitch >= displayInterval) {
    lastDisplaySwitch = now;
    currentPage = (currentPage + 1) % 3;  // 0 → 1 → 2 → 0 ...
    lcd.clear();

    switch (currentPage) {
      case 0:
        // Page 1: Temperature and pH
        lcd.setCursor(0, 0);
        lcd.print("Temp:");
        lcd.print(data.temperature, 1);
        lcd.print((char)223);
        lcd.print("C");

        lcd.setCursor(0, 1);
        lcd.print("pH:");
        lcd.print(data.ph, 1);
        break;

      case 1:
        // Page 2: Humidity and Moisture
        lcd.setCursor(0, 0);
        lcd.print("Humidity:");
        lcd.print(data.humidity, 0);
        lcd.print("%");

        lcd.setCursor(0, 1);
        lcd.print("Moist:");
        lcd.print(data.moisture);
        lcd.print("%");
        lcd.print(data.moistureStatus);
        break;

      case 2:
        // Page 3: NPK values with units (mg/Kg)
        lcd.setCursor(0, 0);
        lcd.print("N:");
        lcd.print(data.nitrogen);
        lcd.print("mg/Kg");

        lcd.setCursor(0, 1);
        lcd.print("P:");
        lcd.print(data.phosphorous);
        lcd.print(" K:");
        lcd.print(data.potassium);
        lcd.print("mg");
        break;
    }
  }
}
