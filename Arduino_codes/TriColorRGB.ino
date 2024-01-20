// 3LED BLINK RGB

const int redPin = D2;
const int greenPin = D3;
const int bluePin = D4;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Red
  setColor(255, 0, 0);
  delay(1000);

  // Green
  setColor(0, 255, 0);
  delay(1000);

  // Blue
  setColor(0, 0, 255);
  delay(1000);
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
