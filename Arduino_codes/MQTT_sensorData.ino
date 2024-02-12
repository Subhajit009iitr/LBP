#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

const char* ssid = "SmartAgr";
const char* password = "Huy3Huy3";
const char* mqttServer = "192.168.137.146";

// const char* ssid = "Galaxy A52s 5GF4CF";
// const char* password = "kwon4758";
// const char* mqttServer = "172.24.23.206";

const int mqttPort = 1883;
const char* topic = "esp8266/data";

WiFiClient espClient;
PubSubClient client(espClient);

#define DHTPIN D2
#define DHTTYPE DHT11 
Adafruit_BMP280 bme;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to MQTT broker
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    if (client.connect("ESP-8266")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.println("Failed to connect to MQTT broker. Retry in 5 seconds...");
      delay(5000);
    }
  }

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
  dht.begin();

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();
  char TempS[10];
  char PresS[10];
  char AltiS[10];
  char HumdS[10];
  char TdhtS[10];
  dtostrf(temperature, 4, 2, TempS);
  dtostrf(pressure, 4, 2, PresS);
  dtostrf(altitude, 4, 2, AltiS);
  dtostrf(humidity, 4, 2, HumdS);
  dtostrf(temp, 4, 2, TdhtS);

  String payload = String(min(temperature,temp))+","+String(max(temperature,temp))+","+String(pressure)+","+String(altitude)+","+String(humidity);

  // client.publish(topic, TempS);
  // client.publish(topic, PresS);
  // client.publish(topic, AltiS);
  // client.publish(topic, HumdS);
  // client.publish(topic, TdhtS);
  client.publish(topic, payload.c_str());


  // Serial.println(TempS);
  // Serial.println(PresS);
  // Serial.println(AltiS);
  // Serial.println(HumdS);
  // Serial.println(TdhtS);
  Serial.println(payload);

  delay(5000);  // Wait for 5 seconds before publishing again
}
