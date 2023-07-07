#include "pico/stdlib.h"
#include <stdio.h>

#include "gps.h"

int main() {
  stdio_init_all();

  GPS gps;
  setup_gps();

  while (true) {
    gps_update(&gps);

    printf("Sats: %i\n", gps.satellites);
  }
}