#include "hardware/timer.h"
#include "pico/time.h"
#include <hardware/adc.h>
#include <pico/stdlib.h>

#include <bluetooth.h>
#include <stdio.h>
#include <stdlib.h>
#include <stepper.h>
#include <string.h>

#define ADC_VREF 3.3f
#define ADC_CONVERSION ADC_VREF / (1 << 12)

void wait_for(bluetooth *bt, const char *message) {
  char *data = NULL;

  while (strcmp(message, data)) {
    if (bluetooth_available(bt)) {
      free(data);
      bluetooth_receive(bt, &data);
    } else
      sleep_ms(5);
  }

  free(data);
}

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

  uint8_t state = 0;

  // Wait for Start
  wait_for(&bt, "start");

  for (int i = 0; i < 2000; i++) {
    stepper_step(&left, 1, 0);
    stepper_step(&right, 1, 0);
    sleep_ms(2);
  }

  // Wait for Dance
  wait_for(&bt, "dance");

  stepper_set(&left, 0, 0, 0, 0);
  stepper_set(&right, 0, 0, 0, 0);

  // Wait for End
  wait_for(&bt, "end");

  while (1)
    ;

  // Main Loop
  while (true) {
    // current time in ms
    uint32_t now = time_us_32() / 1000;

    switch (state) {
      // Reset State
    default:
      state = 0;
      break;

    // Follow Light
    case 0: {
      // Read Light Values
      adc_select_input(0);
      float l = adc_read() * ADC_CONVERSION;
      adc_select_input(1);
      float r = adc_read() * ADC_CONVERSION;

      adc_select_input(2);
      float t = adc_read() * ADC_CONVERSION;

      l = l * (l > t);
      r = r * (r > t);

      if (l < r) {
        // Turn Right
        stepper_step(&left, 1, 0);
        stepper_step(&right, 0, 0);
      } else if (l > r) {
        // Turn Left
        stepper_step(&left, 0, 0);
        stepper_step(&right, 1, 0);
      } else {
        // Move Forward
        stepper_step(&left, 1, 0);
        stepper_step(&right, 1, 0);
      }

      sleep_ms(10);
    } break;

    // TODO
    case 1: {
      //   uint8_t *received_data = NULL;
      //   size_t received_len = 0;
      //   // bluetooth_receive(&bt, &received_data, &received_len);

      //   if (received_data != NULL) {
      //     printf("Received data: %.*s\n", (int)received_len, received_data);
      //     free(received_data);
      //   }

      // Step With Motors
      stepper_step(&left, 1, 1);
      stepper_step(&right, 1, -1);
    } break;
    }
  }
}