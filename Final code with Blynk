// ===== Blynk IoT IDs (MUST be before Blynk includes) =====
#define BLYNK_TEMPLATE_ID   "TMPL64K5Scwnn"
#define BLYNK_TEMPLATE_NAME "ESP32 Env Fan"
#define BLYNK_AUTH_TOKEN    "P0sW8mwevXRpzBFsg2J7-8FC91MqFqoo"
// Optional: see Blynk logs on Serial Monitor
//#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// ===== WiFi =====
const char* WIFI_SSID = "UIU-STUDENT";
const char* WIFI_PASS = "12345678";

// ===== LCD (I2C, 20x4) =====
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Use 0x3F if needed

// ===== DHT22 =====
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ===== Pins =====
const int SOIL_PIN  = 34;  // Soil moisture analog (ADC1, safe)
const int MQ7_PIN   = 35;  // MQ-7 analog (ADC1)
const int RELAY_PIN = 26;  // Relay (fan)

// ===== Relay active level =====
const bool RELAY_ACTIVE_LOW = true;  // true for LOW-level trigger relays

// ===== Thresholds (tune as needed) =====
const int GAS_THRESHOLD       = 2000; // MQ-7 raw threshold (0..4095)
const int SOIL_WATER_PERCENT  = 20;   // >= this % means "in water"

// ===== Blynk Virtual Pins =====
#define VPIN_FAN_SWITCH  V1
#define VPIN_HUMIDITY    V5
#define VPIN_TEMPERATURE V6
#define VPIN_SOIL_PCT    V7
#define VPIN_MQ7_RAW     V8
#define VPIN_SOIL_WATER  V9   // optional
#define VPIN_GAS_FLAG    V10  // optional

BlynkTimer timer;
volatile bool fanOn = false;   // controlled by V1

// ---------------- Helpers ----------------
void setRelay(bool on) {
  if (RELAY_ACTIVE_LOW) {
    digitalWrite(RELAY_PIN, on ? LOW : HIGH);
  } else {
    digitalWrite(RELAY_PIN, on ? HIGH : LOW);
  }
  fanOn = on;
}

// Read sensors, update LCD, publish to Blynk
void readAndPublish() {
  // ---- Read sensors ----
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Celsius

  int soilRaw = analogRead(SOIL_PIN);           // 0..4095
  int soilPct = 100 - ((soilRaw * 100) / 4095); // 100% = wet, 0% = dry
  if (soilPct < 0) soilPct = 0;
  if (soilPct > 100) soilPct = 100;
  bool soilInWater = (soilPct >= SOIL_WATER_PERCENT);

  int gasRaw = analogRead(MQ7_PIN);             // MQ-7 raw value
  bool gasDetected = (gasRaw > GAS_THRESHOLD);

  // ---- LCD (same layout you used) ----
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

  lcd.setCursor(0, 3);
  lcd.print("CO2 gas - ");      // MQ-7 is CO sensor, but keeping your label
  lcd.print(gasRaw);
  lcd.print("    ");

  // ---- Push to Blynk ----
  if (!isnan(h)) Blynk.virtualWrite(VPIN_HUMIDITY, h);
  if (!isnan(t)) Blynk.virtualWrite(VPIN_TEMPERATURE, t);
  Blynk.virtualWrite(VPIN_SOIL_PCT, soilPct);
  Blynk.virtualWrite(VPIN_MQ7_RAW, gasRaw);
  Blynk.virtualWrite(VPIN_SOIL_WATER, soilInWater ? 1 : 0);  // optional
  Blynk.virtualWrite(VPIN_GAS_FLAG,   gasDetected ? 1 : 0);  // optional
}

// -------------- Blynk Callbacks --------------
BLYNK_CONNECTED() {
  // Get last saved state of the fan switch
  Blynk.syncVirtual(VPIN_FAN_SWITCH);
}

BLYNK_WRITE(VPIN_FAN_SWITCH) {
  int v = param.asInt();          // 0 or 1
  setRelay(v == 1);
}

// ---------------- Arduino Setup/Loop ----------------
void setup() {
  Serial.begin(115200);

  // LCD + I2C
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  // Sensors
  dht.begin();
  analogSetAttenuation(ADC_11db);
  pinMode(SOIL_PIN, INPUT);
  pinMode(MQ7_PIN, INPUT);

  // Relay
  pinMode(RELAY_PIN, OUTPUT);
  setRelay(false); // default OFF at boot

  // WiFi + Blynk (single call is enough)
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  // Periodic task: read & publish every 1s
  timer.setInterval(1000L, readAndPublish);

  Serial.println("Blynk + LCD + Sensors started.");
}

void loop() {
  Blynk.run();
  timer.run();
}
