#include <hardware/adc.h>
#include <hardware/timer.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <stdint.h>

#include <bluetooth.h>
#include <stdio.h>
#include <stdlib.h>
#include <stepper.h>
#include <string.h>

void dance(stepper *left, stepper *right);

int main() {
  // Init Motors
  stepper left, right;

  for (int i = 0; i < 4; i++) {
    left.pin[i] = 2 + i;
    right.pin[i] = 6 + i;
  }

  stepper_init(&left);
  stepper_init(&right);

  stepper_set(&left, 0, 0, 0, 0);
  stepper_set(&right, 0, 0, 0, 0);

  // Init Bluetooth
  bluetooth bt;
  bt.TX = 0;
  bt.RX = 1;
  bt.uart = uart0;
  bluetooth_init(&bt);

  // Init Light Sensors
  adc_init();

  adc_gpio_init(26); // left
  adc_gpio_init(27); // right
  adc_gpio_init(28); // top

  // Main Loop
  uint8_t state = 0;
  while (true) {
    // current time in ms
    uint32_t now = time_us_32() / 1000;

    // Get State
    if (bluetooth_available(&bt)) {
      char *data = NULL;
      bluetooth_receive(&bt, &data);

      if (!strcmp(data, "start"))
        state = 1;
      else if (!strcmp(data, "dance"))
        state = 2;
      else if (!strcmp(data, "end"))
        state = 0;
      else
        ;

      free(data);
    }

    switch (state) {
      // Reset State
    default:
      state = 0;
      break;

    // Follow Light
    case 1: {
      // Read Light Values
      adc_select_input(2);
      uint16_t l = adc_read();
      adc_select_input(0);
      uint16_t r = adc_read();

      adc_select_input(1);
      uint16_t f = adc_read();

      uint16_t side = r;
      if (r < l)
        side = l;

      const uint16_t treshold = 4096 / 100;
      if (side > f + treshold && l != r) {
        if (l < r) {
          // Turn Right
          stepper_step(&left, 1, 0);
          stepper_step(&right, -1, 0);
        } else {
          // Turn Left
          stepper_step(&left, -1, 0);
          stepper_step(&right, 1, 0);
        }
      } else {
        // Move Forward
        stepper_step(&left, 1, 0);
        stepper_step(&right, 1, 0);
      }
    } break;

    // Dance
    case 2: {
      dance(&left, &right);
      state = 0;
    } break;
    }

    sleep_ms(2);
  }
}

void move(stepper *lr[2], int dir, int time) {
  const int STOP = 0;
  const int FORWARD = 1;
  const int BACKWARD = 2;
  const int RIGHT = 3;
  const int LEFT = 4;

  int l = 0, r = 0;

  switch (dir) {
  default:
  case STOP:
    l = 0, r = 0;
    break;

  case FORWARD:
    l = 1, r = 1;
    break;

  case BACKWARD:
    l = -1, r = -1;
    break;

  case RIGHT:
    l = 1, r = -1;
    break;

  case LEFT:
    l = -1, r = 1;
    break;
  }
  for (int i = 0; i < time / 2; i++) {
    stepper_step(lr[0], , 0);
    stepper_step(lr[1], 1, 0);
    sleep_ms(2);
  }
}

// Allons-y Danse
void dance(stepper *left, stepper *right) {
  stepper *lr[2] = {left, right};

  // const int STOP = 0;
  const int FORWARD = 1;
  const int BACKWARD = 2;
  const int RIGHT = 3;
  const int LEFT = 4;

  for (int i = 0; i < 4; i++) {
    move(lr, FORWARD, 1000);
    move(lr, LEFT, 1000);
    move(lr, RIGHT, 1000);
    move(lr, BACKWARD, 1000);

    move(lr, LEFT, 1000);
    move(lr, RIGHT, 1000);
    move(lr, FORWARD, 1000);
    move(lr, BACKWARD, 1000);
  }

  move(lr, FORWARD, 1000);
  move(lr, LEFT, 1000);
}