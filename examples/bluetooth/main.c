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

  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

  while (1) {
    char msg[1024];
    bluetooth_receive(&bt, &msg, 1024);
    printf("%s\n", msg);

    bluetooth_send(&bt, "hi");
    sleep_ms(500);
  }
}