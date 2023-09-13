#include "hardware/gpio.h"
#include <gps.h>
#include <stdio.h>

#define ALARM_HOUR 5
#define ALARM_MINUTE 0

int main() {
  stdio_init_all();

  gps_t gps = {};
  setup_gps();

  gpio_init(0);
  gpio_set_dir(0, GPIO_OUT);
  gpio_put(0, 0);

  gpio_init(1);
  gpio_set_dir(1, GPIO_IN);
  gpio_set_pulls(1, true, false);

  while (true) {
    gps_update(&gps);

    if (gps.hour + 2 == ALARM_HOUR && gps.minute == ALARM_MINUTE &&
        gps.second < 15)
      gpio_put(0, 1);

    if (!gpio_get(1))
      gpio_put(0, 0);

    printf("Sats: %02i; Time: %02i:%02i:%02i\n", gps.satellites, gps.hour,
           gps.minute, gps.second);
  }
}