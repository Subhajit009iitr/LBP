#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "SmartAgr";
const char* password = "Huy3Huy3";
const char* mqttServer = "192.168.137.146";  // Replace with your Raspberry Pi's IP address
const int mqttPort = 1883;
const char* topic = "esp8266/data";

WiFiClient espClient;
PubSubClient client(espClient);

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
}

void loop() {
  // Send "Hello, World!" to the MQTT broker
  client.publish(topic, "Hello, World!");

  delay(5000);  // Wait for 5 seconds before publishing again
}
