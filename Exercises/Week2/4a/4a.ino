int positiveInt = 120;
int result = 0;

void setup() {
  Serial.begin(9600);

  Serial.println("");
  
  Serial.println("Positive int in binary:");
  Serial.println(positiveInt, BIN);
  // 0b1111000

  Serial.println("Positive int in decimal:");
  Serial.println(positiveInt);
  // 120

  // Bitwise not:
  result = ~positiveInt;
  
  Serial.println("After bitwise not in binary:");
  Serial.println(result, BIN);
  // 0b11111111111111111111111110000111

  Serial.println("After bitwise not in decimal:");
  Serial.println(result);
  // -121
}

void loop() {
}

/*
With arduino the int data type is a 16-bit value. Unsigned integers thus have a range of 0-65535. 
Signed integers are stored with 2's complement technique, 
here the first bit is used as flag to differentiate negative numbers, then the rest of the bits are inverted and a decimal one is added to the sum.

For example the unsigned value of an 8 bit integer 1000 0000 would be 128, but with 2's complement the first bit indicates the value to be negative.
After this, the resulting 000 0000 is inverted to 111 1111 which would have a value of 127. 
A decimal one is then added and the negative flag taken into account, which will result in a signed value of -128.
*/
