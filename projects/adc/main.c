#include <hardware/adc.h>
#include <stdio.h>

int main() {
  // Init Light Sensors
  stdio_usb_init();

  adc_init();

  adc_gpio_init(26);
  adc_gpio_init(27);

  while (true) {

    // Read Light Values
    adc_select_input(0);
    uint16_t l = adc_read();
    adc_select_input(1);
    uint16_t r = adc_read();

    printf("%i %i\n", l, r);
  }
}