#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// ========== LCD (I2C, 20x4) ==========
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Try 0x27 or 0x3F if not displaying

// ========== DHT22 ==========
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ========== Soil Moisture (Commented Out) ==========
// const int SOIL_PIN = 35;   // ADC1 pin

// ========== MQ-7 + Relay + LED ==========
const int mq7Pin   = 34;   // MQ-7 analog output (ADC1)
const int ledPin   = 25;   // LED indicator
const int relayPin = 26;   // Relay IN pin
int gasLevel = 0;
int threshold = 2000;      // Adjust this based on calibration

void setup() {
  // I2C & LCD setup
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  // Sensor setup
  dht.begin();
  // pinMode(SOIL_PIN, INPUT);   // (Commented)

  pinMode(mq7Pin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  // ---- Read once ----
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // int soilRaw = analogRead(SOIL_PIN);   // (Commented)
  // int soilPct = 100 - (soilRaw * 100 / 4095); // (Commented)
  int soilPct = 50;  // Static placeholder

  gasLevel = analogRead(mq7Pin);
  bool gasDetected = (gasLevel > threshold);

  // Relay + LED
  digitalWrite(ledPin, gasDetected ? HIGH : LOW);
  digitalWrite(relayPin, gasDetected ? HIGH : LOW);

  // ---- Display once (no refresh, no flicker) ----
  lcd.setCursor(0, 0);
  lcd.print("Hum -> ");
  if (isnan(h)) lcd.print("NotFound");
  else { lcd.print(h, 1); lcd.print(" %"); }

  lcd.setCursor(0, 1);
  lcd.print("Temp -> ");
  if (isnan(t)) lcd.print("NotFound");
  else { lcd.print(t, 1); lcd.print(" C"); }

  lcd.setCursor(0, 2);
  lcd.print("MB Humidity -> ");
  lcd.print(soilPct);
  lcd.print("%");

  lcd.setCursor(0, 3);
  lcd.print("Gas -> ");
  lcd.print(gasDetected ? "Yes" : "No");
}

void loop() {
  // No updates, display remains still
}