#include <hardware/adc.h>
#include <pico/stdlib.h>

#include <bluetooth.h>
#include <stepper.h>

#define ADC_VREF 3.3f
#define ADC_CONVERSION ADC_VREF / (1 << 12)

int main() {
  // Init Motors
  stepper left, right;

  for (int i = 0; i < 4; i++) {
    left.pin[i] = i + 0;
    right.pin[i] = i + 4;
  }

  stepper_init(&left);
  stepper_init(&right);

  stepper_set(&left, 0, 0, 0, 0);
  stepper_set(&right, 0, 0, 0, 0);

  // Init Bluetooth
  bluetooth bt;
  bluetooth_init(&bt);

  // Init Light Sensors
  adc_init();

  adc_gpio_init(26); // left
  adc_gpio_init(27); // right
  adc_gpio_init(28); // top

  uint8_t state = 0;

  // Main Loop
  while (true) {
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
      if (bluetooth_available(&bt)) {
        char str[512];
        bluetooth_receive(&bt, str, 512);
      }

      // Step With Motors
      stepper_step(&left, 1, 1);
      stepper_step(&right, 1, -1);
    } break;
    }
  }
}