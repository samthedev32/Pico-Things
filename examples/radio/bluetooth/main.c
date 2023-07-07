#include "boards/pico.h"
#include "hardware/gpio.h"
#include "pico/stdio.h"
#include "pico/time.h"
#include <bluetooth.h>

int main() {
  stdio_init_all();

  sleep_ms(2000);
  printf("Hello, Bluetooth!\n");

  bluetooth bt;

  bt.TX = 0;
  bt.RX = 1;
  bt.uart = uart0;

  bluetooth_init(&bt);

  while (1) {
    if (bluetooth_available(&bt)) {
      char *received_data = NULL;

      bluetooth_receive(&bt, &received_data);
      if (received_data != NULL) {
        printf("Received data: %s\n", received_data);
        free(received_data);
      }
    }
  }
}