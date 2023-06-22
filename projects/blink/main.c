#include "pico/stdlib.h"

int main() {
  gpio_init(2);
  gpio_set_dir(2, GPIO_OUT);

  gpio_init(3);
  gpio_set_dir(3, GPIO_OUT);

  while (true) {
    gpio_put(2, 0);
    gpio_put(3, 1);
    sleep_ms(1000);
  }
}