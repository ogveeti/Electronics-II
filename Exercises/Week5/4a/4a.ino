#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

DS3231 rtc;
RTCDateTime datetime;

// Init the lcd library and set the data pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // 16 columns and 2 rows:
  lcd.begin(16, 2);

  // Init the RTC:
  rtc.begin();

  // Set the RTC time to the time the program is compiled on:
  rtc.setDateTime(__DATE__, __TIME__);
}

void loop() {
  // Update the time:
  datetime = rtc.getDateTime();

  // Display date on the first row:
  lcd.setCursor(0, 0);
  lcd.print(datetime.day);
  lcd.print(".");
  lcd.print(datetime.month);
  lcd.print(".");
  lcd.print(datetime.year);
  
  // Display time on the second row:
  lcd.setCursor(0, 1);
  lcd.print(datetime.hour);
  lcd.print(":");
  lcd.print(datetime.minute);
  lcd.print(":");
  lcd.print(datetime.second);

  // Wait for a second and clear the lcd:
  delay(1000);
  lcd.clear();
}
