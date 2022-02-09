float f = pow(sqrt(2), 2);

void setup() {
  Serial.begin(9600);

  Serial.println(f);

  if (f <= 2.1 && f >= 1.9) {
    Serial.println("True");
  } else {
    Serial.println("Why do we end up here?");
  }
}

void loop() {
}

/*
Arduino uses IEEE-754 system for storing floating point numbers. The values are only approximations and not accurate symbolic representations, which causes issues when doing exact comparisons on values.
Increasing the floating point number precision does not solve the problem completely and floats usually represent some measured real world data with it's own errors,
so it would be preferrable to instead do the comparisons as ranges of the required precision. 

The AVR on 8-bit Arduinos are also missing a hardware floating point unit, which makes these operations extremely slow, so they should not be used if not absolutely necessary.
For example if dealing with currency, it would be wise to calculate everything in cents which are stored as integers, 
and only convert the values to required currency units in the latest state possible, usually when displaying the values in the user interface.
*/
