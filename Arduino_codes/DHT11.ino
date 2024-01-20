// DHT for Humidity and Temperature

#include <DHT.h>

#define DHTPIN D2
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(500); // Delay to let system boot
  Serial.println("DHT11 Humidity & Temperature Sensor\n\n");
  delay(1000); // Wait before accessing the sensor
}

void loop() {
  // Start of Program
  dht.begin();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Current Humidity = ");
  Serial.print(humidity);
  Serial.print("%  ");
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println("°C  ");

  delay(5000); // Wait 5 seconds 

}
