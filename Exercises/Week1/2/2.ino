#define LEDPIN 12
#define BUTTONPIN 11

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT);
  digitalWrite(LEDPIN, LOW); //Init LED to off
  digitalWrite(BUTTONPIN, HIGH); //Enable internal pull-up for switch input
}

void loop() {
  if(!digitalRead(BUTTONPIN)) {
    changeState();
    while(1) {
      if(digitalRead(BUTTONPIN)) {
        break;
      }
    }
  }
}

void changeState() {
    digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}
