#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create LCD object with I2C address and display size
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Try 0x27 or 0x3F if not displaying

void setup() {
  // Initialize I2C with defined pins (optional but good practice)
  Wire.begin(21, 22);

  // Initialize the LCD
  lcd.init();          
  lcd.backlight();     

  // Display messages
  lcd.setCursor(0, 0);
  lcd.print("Hello ESP32!");
  lcd.setCursor(0, 1);
  lcd.print("I2C LCD Test");
}

void loop() {
  // Static display (no updates)
}