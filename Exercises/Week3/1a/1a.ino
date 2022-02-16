// Shift register clock and data lines:
#define srDataPin  8
#define srLatchPin 7
#define srClockPin 6

// Driver pins for each common-cathode digit:
static int cathodePins[] = {3, 2, 4, 5};

// State of individual segments for each letter:
static byte H     = 0b10011011;
static byte E     = 0b11001110;
static byte I     = 0b10000010;
static byte space = 0b00000000;

void setup() {
  pinMode(srDataPin,  OUTPUT);
  pinMode(srLatchPin, OUTPUT);
  pinMode(srClockPin, OUTPUT);
  
  pinMode(cathodePins[0], OUTPUT);
  pinMode(cathodePins[1], OUTPUT);
  pinMode(cathodePins[2], OUTPUT);
  pinMode(cathodePins[3], OUTPUT);
  
  all_digits_off();
}

void loop() {
  display_write(0, H,     false);
  display_write(1, E,     false);
  display_write(2, I,     true);
  display_write(3, space, false);
}
  
void display_write(int digit, byte value, boolean showDecimalPoint) {
  if(showDecimalPoint) {
    bitSet(value, 5);
  }

  all_digits_off();

  // Write the binary data to the shift register and release output latch when done:
  digitalWrite(srLatchPin, LOW);
  shiftOut(srDataPin, srClockPin, MSBFIRST, value);
  digitalWrite(srLatchPin, HIGH);

  // Ground the common-cathode pin for the correct digit:
  digitalWrite(cathodePins[digit], LOW);
  delay(1);
}

// Lift the cathodes from ground:
void all_digits_off() {
  digitalWrite(cathodePins[0], HIGH);
  digitalWrite(cathodePins[1], HIGH);
  digitalWrite(cathodePins[2], HIGH);
  digitalWrite(cathodePins[3], HIGH);
}
