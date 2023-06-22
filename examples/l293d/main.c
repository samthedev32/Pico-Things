#include "pico/stdlib.h"
#include <stdio.h>

#include "l293d.h"

int main() {
  gpio_init(2);
  gpio_init(3);

  gpio_set_dir(2, GPIO_OUT);
  gpio_set_dir(3, GPIO_OUT);

  while (true) {
    gpio_put(2, 1);
    gpio_put(3, 0);
  }
}