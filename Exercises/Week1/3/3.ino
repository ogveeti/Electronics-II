#define ledPin 3
#define sensorPin A5

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {
  analogWrite(ledPin, map(analogRead(sensorPin), 20, 1000, 0, 255));
  delay(10);
}
