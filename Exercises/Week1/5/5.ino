#define analogIn A0
#define buttonIn 19
byte count = 0;

void setup() {
  pinMode(analogIn, INPUT);
  pinMode(buttonIn, INPUT);
  digitalWrite(buttonIn, HIGH); //Enable internal pull-up
  DDRD = B00001111; //Set four rightmost bits on port direction register D, this corresponds to pins 0-3 being outputs
 
}

void loop() {
  if(!digitalRead(buttonIn) || count > 15) {
    count = 0;
  }
  displayCount();
  count++;
  delay(analogRead(analogIn) + 20);
}

void displayCount() {
  PORTD = count; //Write binary count to port state register D, the value cycles from 0b00000000 to 0b00001111
}
