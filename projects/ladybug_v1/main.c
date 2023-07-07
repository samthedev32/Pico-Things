#include <bluetooth.h>
#include <hardware/adc.h>
#include <pico/time.h>
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

  // Init Light Sensors
  adc_init();

  adc_gpio_init(26); // left
  adc_gpio_init(27); // right
  adc_gpio_init(28); // top

  // Init Bluetooth
  bluetooth bt;
  bt.TX = 0;
  bt.RX = 1;
  bt.uart = uart0;
  bluetooth_init(&bt);

  uint8_t state = 0;
  while (true) {
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

    case 1: {
      // Read Light Values
      adc_select_input(0);
      uint16_t l = adc_read();
      adc_select_input(2);
      uint16_t r = adc_read();

      adc_select_input(1);
      uint16_t f = adc_read();

      uint16_t side = r;
      if (r < l)
        side = l;

      const uint16_t treshold = 4096 / 100;
      if (side > f + treshold && l != r) {
        if (l > r) {
          // Turn Right
          stepper_step(&left, 1);
          stepper_step(&right, -1);
        } else {
          // Turn Left
          stepper_step(&left, -1);
          stepper_step(&right, 1);
        }
      } else {
        // Move Forward
        stepper_step(&left, 1);
        stepper_step(&right, 1);
      }
    } break;

    case 2: {
      for (int i = 0; i < 20; i++) {
        stepper_step(&left, -1);
        stepper_step(&right, -1);
        sleep_ms(2);
      }

      for (int i = 0; i < 20; i++) {
        stepper_step(&right, 1);
        stepper_step(&left, 1);
        sleep_ms(2);
      }
    } break;
    }
    sleep_ms(2);
  }
}