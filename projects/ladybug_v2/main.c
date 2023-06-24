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

  // Main Loop
  while (true) {
    stepper_step(&left, 1, 1);
    stepper_step(&right, 1, -1);

    // read light
    adc_select_input(0);
    float left = adc_read() * ADC_CONVERSION;
    adc_select_input(1);
    float right = adc_read() * ADC_CONVERSION;
  }
}