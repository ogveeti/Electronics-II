#define sensorPin A5

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  Serial.println(analogRead(sensorPin));
  delay(10);
}
