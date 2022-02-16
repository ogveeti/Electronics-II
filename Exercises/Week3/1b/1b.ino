// Thermistor power and measurement pins:
#define ntcPowerPin A5
#define ntcInputPin A2

// Shift register clock and data lines:
#define srDataPin  8
#define srLatchPin 7
#define srClockPin 6

// Driver pins for each common-cathode digit:
static int cathodePins[] = {3, 2, 4, 5};

// State of the individual segments for each character:
static byte C = 0b11000110;
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
                                                      
int measuredTemp = 0;
int valueAt0degC = 260;
int valueAt25degC = 510;

void setup() {
  pinMode(ntcPowerPin, OUTPUT);
  
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
  measure_temp();
  show_temp(measuredTemp);
  all_digits_off();
}

void measure_temp() {
  // Turn the voltage divider supply on only momentarily to minimize self-heating:
  digitalWrite(ntcPowerPin, HIGH);
  // Wait for a while and read the voltage divider output:
  delay(1);
  measuredTemp = analogRead(ntcInputPin);
  digitalWrite(ntcPowerPin, LOW);

  // Convert and constrain the raw ADC value into usable units:
  measuredTemp = map(measuredTemp, valueAt0degC, valueAt25degC, 0, 250);
  measuredTemp = constrain(measuredTemp, 0, 999);
}

void show_temp(int tempValue) {
  display_write(3, C, false);
  display_write(2, numbers[((tempValue /   1) % 10)], false);
  display_write(1, numbers[((tempValue /  10) % 10)], true);
  display_write(0, numbers[((tempValue / 100) % 10)], false);
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
