#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Common I2C LCD addresses: 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x3F, 16, 2);  // address, columns, rows

void setup() {
  Wire.begin(D2, D1);   // SDA, SCL for NodeMCU

  lcd.init();           // Initialize LCD
  lcd.backlight();      // Turn on backlight

  lcd.setCursor(0, 0);
  lcd.print("Hello from");

  lcd.setCursor(0, 1);
  lcd.print("NodeMCU ESP8266");

  delay(2000);
  lcd.clear();
}

void loop() {
  static int count = 0;

  lcd.setCursor(0, 0);
  lcd.print("Counter:");

  lcd.setCursor(0, 1);
  lcd.print(count);
  lcd.print("      ");   // clears leftover digits

  count++;
  delay(1000);
}