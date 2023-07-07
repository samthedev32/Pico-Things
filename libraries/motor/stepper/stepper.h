#pragma once

#include <hardware/gpio.h>
#include <pico/stdlib.h>

// Stepper Motor
typedef struct {
  // Blue, Pink, Yellow, Orange Pins
  int pin[4];

  uint8_t position;
} stepper;

// Attach a Stepper Motor
void stepper_attach(stepper *motor) {
  for (int i = 0; i < 4; i++) {
    gpio_init(motor->pin[i]);
    gpio_set_dir(motor->pin[i], GPIO_OUT);
  }

  motor->position = 0;
}

// Set Stepper Motor Pins
void stepper_set(stepper motor, int a, int b, int c, int d) {
  gpio_put(motor.pin[0], a != 0);
  gpio_put(motor.pin[1], b != 0);
  gpio_put(motor.pin[2], c != 0);
  gpio_put(motor.pin[3], d != 0);
}

// "Lock" Stepper Motor
void stepper_lock(stepper motor) { stepper_set(motor, 0, 0, 0, 0); }

// Do a Half Step
void stepper_step_half(stepper *motor, int8_t dir) {
  motor->position += dir;

  // Corrigate Motor Position
  while (motor->position < 0)
    motor->position += 8;
  while (motor->position >= 8)
    motor->position -= 8;

  uint8_t pos = motor->position;
  uint8_t a = pos == 0 || pos == 1 || pos == 7;
  uint8_t b = pos == 1 || pos == 2 || pos == 3;
  uint8_t c = pos == 3 || pos == 4 || pos == 5;
  uint8_t d = pos == 5 || pos == 6 || pos == 7;

  stepper_set(*motor, a, b, c, d);
}

// Do a Full Step
void stepper_step(stepper *motor, int8_t dir) {
  stepper_step_half(motor, dir * 2);
}