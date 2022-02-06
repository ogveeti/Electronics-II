#define buzzerPin 12
#define interruptPin 3

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);

  // State change on pin 3 triggers an interrupt
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptServiceRoutine, CHANGE);
}

// Nested interrupts are disabled by default and this effectively debounces the swich, no need to disable and re-enable interrupts in the ISR
void interruptServiceRoutine() {
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
}
