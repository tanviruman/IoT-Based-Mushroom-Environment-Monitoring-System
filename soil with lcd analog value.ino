/*
  ESP32 Soil Moisture Sensor
  Reads analog value and converts to percentage
*/

int moisture, sensor_analog;
const int sensor_pin = 36;  /* Soil moisture sensor analog output connected to GPIO36 (VP) */

void setup(void) {
  Serial.begin(115200);  /* Set the baudrate to 115200 */
  analogSetAttenuation(ADC_11db);  /* Allows full 0–3.3V input range */
}

void loop(void) {
  sensor_analog = analogRead(sensor_pin);  /* Read analog value (0–4095) */
  
  // Convert to moisture percentage (100% = wet, 0% = dry)
  moisture = 100 - ((sensor_analog / 4095.0) * 100);
  
  Serial.print("Moisture = ");
  Serial.print(moisture);
  Serial.println("%");
  
  delay(1000);  /* Wait for 1 second */
}
