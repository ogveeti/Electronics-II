#include <avdweb_AnalogReadFast.h>

#define ADCpin A0

unsigned int sampleRate; // Can be set between 65,5kHz and 16Hz.
unsigned long timeBetweenSamples; // Stored as microseconds.

unsigned long storedMicroseconds = 0;

// Sample memory:
#define memoryDepth 512
byte ADCreadings[memoryDepth];
unsigned int timeFromPreviousSample[memoryDepth];
int sampleCounter = 0;

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.print("handshake");
  Serial.println();
  
  while (!Serial.available()){}   // Wait for the sampling rate information to be available.
  sampleRate = Serial.parseInt();
  timeBetweenSamples = 1000000 / sampleRate;
}

void loop() {
  // First sample into empty memory:
  if(sampleCounter == 0) {    
    timeFromPreviousSample[sampleCounter] = 0;
    storedMicroseconds = micros();
    //Store the ADC readings as 8 bit values to save space:
    ADCreadings[sampleCounter] = map(analogReadFast(ADCpin), 0, 1023, 0, 255);
    sampleCounter++;

    // Subsequent samples:
  } else if(sampleCounter < memoryDepth) {
    if(micros() >= storedMicroseconds + timeBetweenSamples) {
      // Store the time difference between the start of each conversion:
      timeFromPreviousSample[sampleCounter] = micros() - storedMicroseconds;
      storedMicroseconds = micros();
      ADCreadings[sampleCounter] = map(analogReadFast(ADCpin), 0, 1023, 0, 255);
      sampleCounter++;
    }

    // Sample memory full:
  } else {
    sampleCounter = 0;
    transmitData();
  }
}

void transmitData() {
  for(int i = 0; i < memoryDepth; i++) {
    Serial.print(timeFromPreviousSample[i]);
    Serial.print(",");
    Serial.print(ADCreadings[i]);
    Serial.println();
  }

  // Send a transmit complete message, this will trigger a display refresh in the graphing software:
  Serial.print("complete");
  Serial.println();

  // Wait for the graphing software to refresh the display, continue sampling after a message is received:
  while (!Serial.available()){}
}
