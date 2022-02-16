// Switch input:
#define interruptPin 2

// Shift register clock and data lines:
#define srDataPin  10
#define srLatchPin 9
#define srClockPin 8

// Driver pins for each common-cathode digit:
static int cathodePins[] = {4, 3, 5, 6};

// State of the individual segments for each number:
static byte numbers[10] = {0b11010111,  // 0
                           0b00010001,  // 1
                           0b11001101,  // 2
                           0b01011101,  // 3
                           0b00011011,  // 4
                           0b01011110,  // 5
                           0b11011110,  // 6
                           0b00010101,  // 7
                           0b11011111,  // 8
                           0b01011111}; // 9

// Display buffer:
int digitValues[4] = {0, 0, 0, 0};

volatile int fallingEdges = 0;

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  
  pinMode(srDataPin,  OUTPUT);
  pinMode(srLatchPin, OUTPUT);
  pinMode(srClockPin, OUTPUT);
  
  pinMode(cathodePins[0], OUTPUT);
  pinMode(cathodePins[1], OUTPUT);
  pinMode(cathodePins[2], OUTPUT);
  pinMode(cathodePins[3], OUTPUT);
  
  all_digits_off();

  // Falling edge on pin 2 triggers an interrupt
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptServiceRoutine, FALLING);
}

void loop() {
  delay(5000);
  displayNumber(fallingEdges);
  fallingEdges = 0;
}

void interruptServiceRoutine() {
  fallingEdges++;
}

void displayNumber(int number) {
  digitValues[3] = ((number /    1) % 10);
  digitValues[2] = ((number /   10) % 10);
  digitValues[1] = ((number /  100) % 10);
  digitValues[0] = ((number / 1000) % 10);
  
  for(int i = 0; i < 600; i++) {
    for(int j = 3; j >= 0; j--) {
      update_display(j, numbers[digitValues[j]]);
    }
  }
}

void update_display(int digit, byte value) {
  // Write the binary data to the shift register and release output latch when done:
  digitalWrite(srLatchPin, LOW);
  shiftOut(srDataPin, srClockPin, MSBFIRST, value);
  digitalWrite(srLatchPin, HIGH);

  // Ground the common-cathode pin for the correct digit:
  digitalWrite(cathodePins[digit], LOW);
  delay(1);
  all_digits_off();
}

// Lift the cathodes from ground:
void all_digits_off() {
  digitalWrite(cathodePins[0], HIGH);
  digitalWrite(cathodePins[1], HIGH);
  digitalWrite(cathodePins[2], HIGH);
  digitalWrite(cathodePins[3], HIGH);
}
