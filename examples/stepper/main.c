#include "pico/stdlib.h"
#include <stdio.h>

#include "stepper.h"

int main() {
  stepper motor;

  // Set Pins(2..5)
  for (int i = 0; i < 4; i++)
    motor.pin[i] = 2 + i;

  stepper_init(&motor);

  while (true) {
    stepper_step(&motor, 1, 1);
  }
}