#include "LedControl.h"
#include "arduinoFFT.h"

// The current max frequency is roughly 9kHz. Faster sampling rates would require faster FFT calculation, data acquisition and display driving. Fixed point math should be used for the FFT and hardware SPI for the display.
// The AD-conversion is currently a free-running process, this means the resulting frequency values are only relative to each other.
// Absolute frequency values would require a known sampling rate based on a timer.

// The visible data can be scrolled horizontally since we are taking 32 samples and only 8 can be shown on the display at a time.
// The horizontal offset parameter currently works as a multiple of display widths, the offset could however be set even with a single sample resolution if needed. 

const byte horizontalOffset = 1;

#define dataPin 12
#define clockPin 11
#define chipSelect 10
#define numberOfDisplays 1

#define amountOfSamples 32
#define displayWidth 8

// Vectors for storing the real and imaginary components of the samples before and after transform:
double realVector[amountOfSamples];
double imaginaryVector[amountOfSamples];

// Display column height helper:
const byte barGraphValues[] = {0b00000000,
                               0b00000001,
                               0b00000011,
                               0b00000111,
                               0b00001111,
                               0b00011111,
                               0b00111111,
                               0b11111111};

// Class constructors:
arduinoFFT FFT = arduinoFFT();
LedControl LC = LedControl(dataPin, clockPin, chipSelect, numberOfDisplays);

void setup() {
  initDisplay();
}

void loop() {
  sample();
  calculateFFT();
  updateDisplay();
}

void sample() {
  for (int i = 0; i < amountOfSamples; i++) {
    realVector[i] = analogRead(A0);
    imaginaryVector[i] = 0;
  }
}

void calculateFFT() {
  FFT.DCRemoval(); // Remove the DC offset from the sampled values.
  FFT.Windowing(realVector, amountOfSamples, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD);
  FFT.Compute(realVector, imaginaryVector, amountOfSamples, FFT_FORWARD);
  FFT.ComplexToMagnitude(realVector, imaginaryVector, amountOfSamples);
}

void drawColumn(int index, int height) {
  LC.setColumn(0, index, barGraphValues[height]);
}

void updateDisplay() {
  for (int i = 0; i < displayWidth; i++) {
    byte mappedValue = map((byte)realVector[i + (horizontalOffset*displayWidth)], 0, 150, 1, 7);
    drawColumn(i, constrain(mappedValue, 1, 7));
  }
}

void initDisplay() {
  LC.shutdown(0, false); // Turn the display on.
  LC.setIntensity(0, 8); // Set brightness between 0 and 15.
  LC.clearDisplay(0);
}
