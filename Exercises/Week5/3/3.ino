#include <LiquidCrystal.h>

String poem = "This is a short poem.";

// Init library and set the data pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // 16 columns and 2 rows:
  lcd.begin(16, 2);
  // Set the initial cursor position:
  lcd.setCursor(16, 0);
  // Enable automatic scrolling:
  lcd.autoscroll();
}

void loop() {
  for (int i = 0; i < poem.length(); i++) {
    lcd.print(poem.charAt(i));
    delay(300);
  }

  for (int i = 0; i < 16; i++) {
    lcd.print(" ");
    delay(300);
  }
  
  // Clear the screen and reset cursor position
  lcd.clear();
  lcd.setCursor(16, 0);
  delay(300);
}
