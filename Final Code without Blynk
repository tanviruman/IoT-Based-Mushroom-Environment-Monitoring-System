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
// const int LED_PIN   = 25;  // LED indicator (soil-in-water)
// const int RELAY_PIN = 26;  // Relay (gas)

// ===== Thresholds (tune as needed) =====
const int GAS_THRESHOLD       = 2000; // MQ-7 raw threshold (0..4095)
const int SOIL_WATER_PERCENT  = 20;   // >= this % means "in water"

// ---------------------------------------------------------------------
// MERGED: Relay Fan Test section (as-is, plus minimal integration)
// ---------------------------------------------------------------------
/***** ESP32 + 1-Channel Relay — Fan Wiring Test (NO Blynk) *****/
// === EDIT BELOW ===
const int RELAY_PIN = 26;            // Use a safe GPIO (26/27 are good)
const bool RELAY_ACTIVE_LOW = true;  // true for LOW-level trigger relays; false for HIGH-level
// Choose one mode: 0=ALWAYS_OFF, 1=ALWAYS_ON, 2=BLINK
const int MODE = 0;                  // <- change this to 0/1/2 to test
unsigned long ON_MS  = 2000;         // BLINK: relay ON duration (ms)
unsigned long OFF_MS = 2000;         // BLINK: relay OFF duration (ms)
// === EDIT ABOVE ===

void setRelay(bool on) {
  if (RELAY_ACTIVE_LOW) {
    digitalWrite(RELAY_PIN, on ? LOW : HIGH);
  } else {
    digitalWrite(RELAY_PIN, on ? HIGH : LOW);
  }
}
static bool relayBlinkOn = false;
static unsigned long relayT0 = 0;
// ---------------------------------------------------------------------

void setup() {
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  dht.begin();

  analogSetAttenuation(ADC_11db);

  pinMode(SOIL_PIN, INPUT);
  pinMode(MQ7_PIN, INPUT);

  pinMode(RELAY_PIN, OUTPUT);

  if (MODE == 0) {
    setRelay(false);
  } else if (MODE == 1) {
    setRelay(true);
  } else {
    setRelay(false);
  }

  Serial.begin(115200);
  Serial.println("Relay Fan Test Started");
}

void loop() {
  // ---- Read sensors ----
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  int soilRaw = analogRead(SOIL_PIN);                 // 0..4095
  int soilPct = 100 - ((soilRaw * 100) / 4095);       // 100% = wet, 0% = dry
  if (soilPct < 0) soilPct = 0;
  if (soilPct > 100) soilPct = 100;
  bool soilInWater = (soilPct >= SOIL_WATER_PERCENT);

  int gasRaw = analogRead(MQ7_PIN);                   // <-- MQ7 raw value
  bool gasDetected = (gasRaw > GAS_THRESHOLD);

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
  if (soilPct < 10) lcd.print(" "); 
  lcd.print(soilPct); lcd.print("% ");
  lcd.print(soilInWater ? "Yes " : "No  ");

  // ===== Modified Output Line =====
  lcd.setCursor(0, 3);
  lcd.print("CO2 gas - ");
  lcd.print(gasRaw);             // ✅ Show raw analog value instead of "Yes/No"
  lcd.print("    ");             // padding to clear old text

  // ---- Relay Logic (unchanged) ----
  if (MODE == 0) {
    // Fan always OFF
  } else if (MODE == 1) {
    // Fan always ON
  } else {
    unsigned long now = millis();
    unsigned long interval = relayBlinkOn ? ON_MS : OFF_MS;
    if (now - relayT0 >= interval) {
      relayBlinkOn = !relayBlinkOn;
      setRelay(relayBlinkOn);
      relayT0 = now;
      Serial.print("Relay: ");
      Serial.println(relayBlinkOn ? "ON" : "OFF");
    }
  }

  delay(800);
}
