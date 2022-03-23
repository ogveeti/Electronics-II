#define analogIn A5  //Input for the potentiometer
#define enablePin 9  //Motor driver enable, controlled with PWM
#define statePin1 8  //Motor driver state for channel 1
#define statePin2 7  //Motor driver state for channel 2

int analogValue = 0;  //Store the analog input value

void setup() {
  pinMode(enablePin, OUTPUT);
  pinMode(statePin1, OUTPUT);
  pinMode(statePin2, OUTPUT);

  analogWrite(enablePin, 0);
  digitalWrite(statePin1, LOW);
  digitalWrite(statePin2, LOW);
}

void loop() {
  analogValue = analogRead(analogIn);

  if(analogValue < 500) {
    //Set motor direction to CCW:
    digitalWrite(statePin1, HIGH);
    digitalWrite(statePin2, LOW);
    
    //Set the motor speed:
    analogWrite(enablePin, map(analogValue, 499, 0, 0, 255));
    
  } else if(analogValue > 522) {
    //Set motor direction to CW:
    digitalWrite(statePin1, LOW);
    digitalWrite(statePin2, HIGH);

    //Set the motor speed:
    analogWrite(enablePin, map(analogValue, 523, 1023, 0, 255));
    
  } else {
    //Motor off:
    analogWrite(enablePin, 0);
    digitalWrite(statePin1, LOW);
    digitalWrite(statePin2, LOW);
  }

  //Constrain the loop speed a bit:
  delay(100);
}
