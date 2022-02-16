#define ledPin 12
#define interruptPin 2

boolean timerSet = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), risingInterrupt, RISING);
}

// Turn the led on and start the waiting period when the sensor detects movement.
// The pulse length is timed in software as the potentiometer control on the sensor wasn't reliable, the sensor is set to repeating trigger mode with the jumper link.
void risingInterrupt() {
  digitalWrite(ledPin, HIGH);
  timerSet = true;
}

void loop() {
  // Wait for 5 seconds after the interrupt has been triggered:
  if(timerSet) {
    delay(5000);
    timerSet = false;
  }

  // Turn the led off if the sensor input falls to zero after the delay:
  if(digitalRead(interruptPin) == LOW) {
    digitalWrite(ledPin, LOW);
  }
}
