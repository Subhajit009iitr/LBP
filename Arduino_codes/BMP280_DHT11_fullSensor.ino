#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

#define DHTPIN D2
#define DHTTYPE DHT11 
Adafruit_BMP280 bme;
DHT dht(DHTPIN, DHTTYPE);

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

  Serial.println("Your Values: \n");
  // Print the converted values with explicit formatting
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);  // Print with 2 decimal places
  Serial.println("°C ");

  Serial.print("Pressure: ");
  Serial.print(pressure, 2);  // Print with 2 decimal places
  Serial.println(" hPa");

  Serial.print("Altitude: ");
  Serial.print(altitude, 2);  // Print with 2 decimal places
  Serial.println(" m");

  Serial.println();

  dht.begin();

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  Serial.print("Current Humidity = ");
  Serial.print(humidity);
  Serial.print("\n ");
  Serial.print("DHT Temperature = ");
  Serial.print(temp);
  Serial.println("°C  ");

  Serial.println();

  // Wait 1 second
  delay(5000);
}
