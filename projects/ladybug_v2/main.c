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

extern void dance(stepper *left, stepper *right);

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
    case 0:
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

// Dance Program
void dance(stepper *left, stepper *right) {
  stepper_step(left, 1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);
  // elore
  stepper_step(left, -1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);
  // balra kor
  stepper_step(left, 1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);
  // jobbra kor
  stepper_step(left, -1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);

  // hatra
  stepper_step(left, -1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);

  // balra kor
  stepper_step(left, 1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);

  // jobbra kor
  stepper_step(left, 1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);

  // elore
  stepper_step(left, -1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);

  // hatra
  stepper_step(left, 1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);

  // elore
  stepper_step(left, -1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);

  // balra kor
  stepper_step(left, 1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);

  // jobbra kor

  stepper_step(left, -1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);

  // hatra

  stepper_step(left, -1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);

  // balra kor
  stepper_step(left, 1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);

  // jobbra kor
  stepper_step(left, 1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);

  // elore
  stepper_step(left, -1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);

  // hatra
  stepper_step(left, 1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);

  // elore
  stepper_step(left, -1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);

  // balra kor
  stepper_step(left, 1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);

  // jobbra kor
  stepper_step(left, -1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);

  // hatra
  stepper_step(left, -1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);

  // balra kor
  stepper_step(left, 1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);

  // jobbra kor
  stepper_step(left, 1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);

  // elore
  stepper_step(left, -1, 0);
  stepper_step(right, -1, 0);
  sleep_ms(1000);

  // hatra
  stepper_step(left, 1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);

  // elore
  stepper_step(left, -1, 0);
  stepper_step(right, 1, 0);
  sleep_ms(1000);
}