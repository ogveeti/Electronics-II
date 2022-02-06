// Timer 1 is used by PWM pins 9 and 10, timer 2 is used by PWM pin 11. Timer 0 is left available for generating interrupts.
// On an Arduino Uno, the timer 0 is already set up for millisecond timing with a roughly 1 KHz frequency. 
// The exact overflow frequency of the 8 bit counter with 16 MHz clock speed and a prescaler value of 64 is 976,5625Hz (16000000Hz/64/256).

// Define output pins:
#define redPin   9
#define greenPin 10
#define bluePin  11

// Store the next chosen colour:
int colour = 1;

// Store the interrupt count:
int interruptCount = 0;

// Define the RGB values for each colour:
const int red[]     = {255, 0, 0};
const int green[]   = {0, 255, 0};
const int blue[]    = {0, 0, 255};
const int yellow[]  = {255, 255, 0};
const int magenta[] = {255, 0, 255};
const int cyan[]    = {0, 255, 255};

// Make the RGB values easily accessable by storing their memory locations in an array:
const int* colours[] = {red, 
                        green, 
                        blue, 
                        yellow, 
                        magenta, 
                        cyan};

// See section 14 from ATmega328P datasheet for register descriptions and reference.
void setup() {  
  // Set Output compare register A to 128. Output compare unit raises an interrupt flag every time the value of timer 0 matches this:
  OCR0A = 0b10000000; 
  // Set the Timer/Counter0 Output Compare Match A Interrupt Enable bit from Timer/Counter0 Interrupt Mask Register:
  TIMSK0 |= _BV(OCIE0A);
  
  // Start with colour red:
  setColour(colours[0]);
}

ISR(TIMER0_COMPA_vect) {
  // Reset the interrupt counter and change colour at roughly 1Hz intervals:
  if(interruptCount >= 1000) {
    interruptCount = 0;
    cycle();
  }

  interruptCount++;
}

void cycle() {
  setColour(colours[colour]);
  colour++;
  if (colour > 5) {
    colour = 0;
  }
}

void setColour(int rgbValues[3]) {
  analogWrite(redPin,   rgbValues[0]);
  analogWrite(greenPin, rgbValues[1]);
  analogWrite(bluePin,  rgbValues[2]);
}

void loop() {
}
