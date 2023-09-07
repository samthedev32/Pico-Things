#include "hardware/gpio.h"
#include <gps.h>
#include <stdio.h>

int main() {
  stdio_init_all();

  gps_t gps;
  setup_gps();

  gpio_init(0);
  gpio_set_dir(0, GPIO_OUT);

  int state = 0;

  while (true) {
    gps_update(&gps);

    if (gps.second % 5 == 0) {
      state = !state;
      gpio_put(0, state);
    }

    printf("Sats: %02i; Time: %02i:%02i:%02i; %03i \n", gps.satellites,
           gps.hour, gps.minute, gps.second, gps.altitude);
  }
}