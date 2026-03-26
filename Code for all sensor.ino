#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// ===== LCD (I2C, 20x4) =====
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Use 0x3F if needed

// ===== DHT22 =====
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ===== Pins (moved SOIL from 12 -> 34 to avoid boot flash issue) =====
const int SOIL_PIN  = 34;  // Soil moisture analog (ADC1, safe)
const int MQ7_PIN   = 35;  // MQ-7 analog (ADC1)
const int LED_PIN   = 25;  // LED indicator (soil-in-water)
const int RELAY_PIN = 26;  // Relay (gas)

// ===== Thresholds (tune as needed) =====
const int GAS_THRESHOLD       = 2000; // MQ-7 raw threshold (0..4095)
const int SOIL_WATER_PERCENT  = 50;   // >= this % means "in water"

void setup() {
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  dht.begin();

  // Full 0–3.3V range on ADC1 pins
  analogSetAttenuation(ADC_11db);
  // (Optional: per-pin) analogSetPinAttenuation(SOIL_PIN, ADC_11db);
  // (Optional: per-pin) analogSetPinAttenuation(MQ7_PIN,  ADC_11db);

  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  // ADC1 pins (32–39) are input-only; pinMode for them is not required but harmless.
  pinMode(SOIL_PIN, INPUT);
  pinMode(MQ7_PIN, INPUT);
}

void loop() {
  // ---- Read sensors ----
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  int soilRaw = analogRead(SOIL_PIN);                 // 0..4095
  int soilPct = 100 - ((soilRaw * 100) / 4095);       // 100% = wet, 0% = dry
  if (soilPct < 0) soilPct = 0;
  if (soilPct > 100) soilPct = 100;
  bool soilInWater = (soilPct >= SOIL_WATER_PERCENT); // LED logic

  int gasRaw = analogRead(MQ7_PIN);
  bool gasDetected = (gasRaw > GAS_THRESHOLD);        // Relay logic

  // ---- Actuators ----
  digitalWrite(LED_PIN,   soilInWater ? HIGH : LOW);  // LED on if soil in water
  digitalWrite(RELAY_PIN, gasDetected ? HIGH : LOW);  // Relay on if gas detected

  // ---- LCD ----
  lcd.setCursor(0, 0);
  lcd.print("Humidity - ");
  if (isnan(h)) { lcd.print("NotFound    "); }
  else { lcd.print(h, 1); lcd.print(" %    "); }

  lcd.setCursor(0, 1);
  lcd.print("  Temp- ");
  if (isnan(t)) { lcd.print("NotFound   "); }
  else { lcd.print(t, 1); lcd.print(" C    "); }

  lcd.setCursor(0, 2);
  lcd.print("MB Moisture-");
  if (soilPct < 10) lcd.print(" ");      // alignment nicety
  lcd.print(soilPct); lcd.print("% ");
  lcd.print(soilInWater ? "Yes " : "No  ");

  lcd.setCursor(0, 3);
  lcd.print("CO2 gas - ");
  lcd.print(gasDetected ? "Yes     " : "No      ");

  delay(800); // gentle refresh, no flicker
}
