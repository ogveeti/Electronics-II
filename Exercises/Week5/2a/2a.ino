#include <Stepper.h>

// Number of steps for one rotation:
#define stepsPerFullRotation 2048

// Init the library:
Stepper motor = Stepper((stepsPerFullRotation), 8, 10, 9, 11);

void setup() {
  // Set the speed to 15rpm:
  motor.setSpeed(15);
}

void loop() {
  // Run a full revolution in one direction:
  motor.step(stepsPerFullRotation);
  delay(500);
  
  // Run a full revolution in the other direction:
  motor.step(-stepsPerFullRotation);
  delay(500);
}
