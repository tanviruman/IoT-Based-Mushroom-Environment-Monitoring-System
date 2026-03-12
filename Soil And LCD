/*
  ESP32 Soil Moisture Sensor + I2C LCD (20x4)
  Reads analog value and converts to percentage, shows on LCD
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int moisture, sensor_analog;
const int sensor_pin = 34;  /* Soil moisture sensor analog output connected to GPIO34 */

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Try 0x27 or 0x3F if not displaying

void setup(void) {
  Serial.begin(115200);               /* Set the baudrate to 115200 */
  analogSetAttenuation(ADC_11db);     /* Allows full 0–3.3V input range */

  Wire.begin(21, 22);                 // I2C pins for ESP32
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop(void) {
  sensor_analog = analogRead(sensor_pin);  /* Read analog value (0–4095) */

  // Convert to moisture percentage (100% = wet, 0% = dry)
  moisture = 100 - ((sensor_analog / 4095.0) * 100);

  // Serial output
  Serial.print("Moisture = ");
  Serial.print(moisture);
  Serial.println("%");

  // LCD output (percentage only)
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisture);
  lcd.print("%   ");

  delay(1000);  /* Wait for 1 second */
}
