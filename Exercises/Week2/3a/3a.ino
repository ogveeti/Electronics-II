#include "pitches.h"

#define buzzerPin 11

// Save the notes in the melody
static int notes[] = {NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4, 
                      NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4, 
                      NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4, 
                      NOTE_A4};

// Save the duration for each note
static int durations[] = {8, 8, 4, 4,
                          8, 8, 4, 4,
                          8, 8, 4, 4,
                          2};

void setup() {
}

void loop() {
  // Iterate over the melody:
  for (int note = 0; note < 13; note++) {
    // Calculate the tone length for each note by dividing one second with the note duration:
    int time = 1000 / durations[note];
    // Play the note:
    tone(buzzerPin, notes[note], time);
    // Pause between notes:
    delay(time);
  }

  delay(5000);
}
