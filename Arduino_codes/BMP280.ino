#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bme;

void setup() {
  Serial.begin(9600);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  uint32_t pressureRaw = bme.readPressure();

  float temperature = bme.readTemperature();
  float pressure = bme.seaLevelForAltitude(0, pressureRaw / 100.0);
  float altitude = bme.readAltitude(1013.25);

  // Print the converted values with explicit formatting
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);  // Print with 2 decimal places
  Serial.println(" *C");

  Serial.print("Pressure: ");
  Serial.print(pressure, 2);  // Print with 2 decimal places
  Serial.println(" hPa");

  Serial.print("Altitude: ");
  Serial.print(altitude, 2);  // Print with 2 decimal places
  Serial.println(" m");

  // Wait 1 second
  delay(1000);
}
