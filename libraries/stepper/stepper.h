#include <pico/stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#define STEPPER_FULL_STEP_SEQUENCES 4
#define STEPPER_HALF_STEP_SEQUENCES STEPPER_FULL_STEP_SEQUENCES * 2

typedef struct {
  // Blue, Pink, Yellow, Orange Pins
  int pin[4];

  // Step Status
  uint8_t position;
} stepper;

void stepper_init(stepper *motor) {
  for (int i = 0; i < 4; i++) {
    gpio_init(motor->pin[i]);
    gpio_set_dir(motor->pin[i], GPIO_OUT);
  }

  motor->position = 0;
}

void stepper_set(stepper *motor, int a, int b, int c, int d) {
  gpio_put(motor->pin[0], a != 0);
  gpio_put(motor->pin[1], b != 0);
  gpio_put(motor->pin[2], c != 0);
  gpio_put(motor->pin[3], d != 0);
}

void stepper_step(stepper *motor, int steps, int speed) {
  int dir = 0;
  if (steps < 0)
    dir = -1;
  else
    dir = 1;

  for (int i = 0; i < steps; i++) {
    motor->position += dir;

    while (motor->position < 0)
      motor->position += STEPPER_FULL_STEP_SEQUENCES;

    while (motor->position >= STEPPER_FULL_STEP_SEQUENCES)
      motor->position -= STEPPER_FULL_STEP_SEQUENCES;

    // Step
    stepper_set(motor, motor->position == 0, motor->position == 1,
                motor->position == 2, motor->position == 3);

    sleep_us(speed);
  }
}

void stepper_step_half(stepper *motor, int steps, int speed) {
  int dir = 0;
  if (steps < 0)
    dir = -1;
  else
    dir = 1;

  for (int i = 0; i < steps; i++) {
    motor->position += dir;

    while (motor->position < 0)
      motor->position += STEPPER_HALF_STEP_SEQUENCES;

    while (motor->position >= STEPPER_HALF_STEP_SEQUENCES)
      motor->position -= STEPPER_HALF_STEP_SEQUENCES;

    // Step
    int pos = motor->position / 2;
    stepper_set(motor, pos == 0, pos == 1, pos == 2, pos == 3);

    sleep_us(speed);
  }
}