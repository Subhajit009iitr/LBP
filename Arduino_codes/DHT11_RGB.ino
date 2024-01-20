#include <DHT.h>

#define DHTPIN D2
#define DHTTYPE DHT11

#define RED_PIN D5     
#define GREEN_PIN D6   
#define BLUE_PIN D7    

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(500); // Delay to let system boot
  Serial.println("DHT11 Humidity & Temperature Sensor\n\n");
  delay(1000); // Wait before accessing the sensor

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
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

  // Control RGB LED based on humidity
  if (humidity < 75) {
    setColor(0, 255, 0);  // Blue
  } else if (humidity >= 75 && humidity <= 90) {
    setColor(0, 0, 255);  // Green
  } else {
    setColor(255, 0, 0);  // Red
  }

  delay(5000); // Wait 5 seconds
}

// Function to set the color of the RGB LED
void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}
