#include <Keypad.h>

#define buzzerPin 11

// Define the keypad size
#define rowSize 4
#define columnSize 4

// Define the keypad pins
const byte rowPins[rowSize] = {7, 6, 5, 4};
const byte columnPins[columnSize] = {3, 2, 1, 0};

// Define the keypad buttons
const char keyValues[rowSize][columnSize] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Define the frequency for each note:
const int C  = 523;
const int D  = 587;
const int E  = 659;
const int F  = 698;
const int G  = 784;
const int A  = 880;
const int H  = 987;

// Create a new keypad object
Keypad myKeys = Keypad(makeKeymap(keyValues), rowPins, columnPins, rowSize, columnSize);

void setup()  {
}

void loop() {
  char key = myKeys.getKey();
  
  if (key)  {
    switch (key) {
    case '1':
      tone(buzzerPin, C, 500);
      break;
      
    case '2':
      tone(buzzerPin, D, 500);
      break;
      
    case '3':
      tone(buzzerPin, E, 500);
      break;
      
    case '4':
      tone(buzzerPin, F, 500);
      break;
      
    case '5':
      tone(buzzerPin, G, 500);
      break;
      
    case '6':
      tone(buzzerPin, A, 500);
      break;
      
    case '7':
      tone(buzzerPin, H, 500);
      break;
      
    default:
      break;
    }
   key = '*'; 
  }
}
