#include <ESP8266WiFi.h>

// Replace with your Wi-Fi credentials
const char *ssid = "Galaxy A52s 5GF4CF";
const char *password = "kwon4758";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectToWiFi();
}

void loop() {
    
}

void connectToWiFi() {
  Serial.println("Connecting to Wi-Fi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
