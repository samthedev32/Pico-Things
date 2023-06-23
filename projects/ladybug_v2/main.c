#include <pico/stdlib.h>
#include <stepper.h>

int main() {
  // Init Motors
  stepper left, right;

  for (int i = 0; i < 4; i++) {
    left.pin[i] = i + 0;
    right.pin[i] = i + 4;
  }

  stepper_init(&left);
  stepper_init(&right);

  while (true) {
    stepper_step(&left, 1, 1);
    stepper_step(&right, 1, -1);
  }
}