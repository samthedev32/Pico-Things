#include "stepper.h"

int main() {
  // Attach Stepper
  stepper motor;
  for (int i = 0; i < 4; i++)
    motor.pin[i] = i;

  stepper_attach(&motor);

  while (1) {
    // Step Forward
    stepper_step(&motor, 1);
    sleep_ms(800);
  }

  // "Lock" Stepper, so it isn't under stress
  stepper_lock(motor);

  return 0;
}