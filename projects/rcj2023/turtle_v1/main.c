#include <stepper.h>

int main() {
  // Init Motors
  stepper left, right;

  for (int i = 0; i < 4; i++) {
    left.pin[i] = 2 + i;
    right.pin[i] = 6 + i;
  }

  stepper_attach(&left);
  stepper_attach(&right);

  stepper_lock(left);
  stepper_lock(right);

  uint8_t state = 0;
  while (true) {
    switch (state) {

    // Reset State
    default:
    case 0:
      state = 0;
      break;
    }

    sleep_ms(2);
  }
}