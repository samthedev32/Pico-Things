#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include "sd.h"
#include <stdlib.h>

#define SAMPLE_RATE 60

#define LED 0
#define BUTTON 1

void blink(int pin, int delay) {
  gpio_put(pin, 1);
  sleep_ms(delay);
  gpio_put(pin, 0);
  sleep_ms(delay);
}

void trigger(int pin) {
  while (gpio_get(BUTTON))
    ;
  while (!gpio_get(BUTTON))
    ;
}

int main() {
  // Init LED
  gpio_init(LED);
  gpio_set_dir(LED, GPIO_OUT);
  gpio_put(LED, 1);
  sleep_ms(100);
  gpio_put(LED, 0);

  // Init Button
  gpio_init(BUTTON);
  gpio_set_dir(BUTTON, GPIO_IN);
  gpio_set_pulls(BUTTON, true, false);

  sd *card = sd_init();

  // Wait for SD Card
  while (sd_mount(card)) {
    blink(LED, 300);
  }

  gpio_init(4);
  gpio_set_dir(4, GPIO_OUT);
  gpio_put(4, 1);
  sleep_ms(100);
  gpio_put(4, 0);

  size_t size = SAMPLE_RATE * (3 * 60); // set for 3 minutes
  size_t cursor = 0;
  float *data = (float *)malloc(sizeof(float) * size);

  if (!data)
    blink(LED, 100);

  // Wait For ButtonPress
  trigger(BUTTON);

  // Start Logging
  gpio_put(LED, 1);
  while (gpio_get(BUTTON)) {
    // Resize Buffer
    while (cursor >= size) {
      gpio_put(LED, 0);
      size *= 2;
      float *temp = (float *)realloc(data, sizeof(float) * size);

      if (!temp) {
        // Can't Resize Buffer, quit
      }

      gpio_put(LED, 1);
    }
    // data[cursor] =
  }

  // Write to File
  file_open(card, "data.bin", FA_WRITE | FA_CREATE_ALWAYS);

  file_write(card, "Hello from the Pico!\n");

  file_close(card);

  sd_unmount();

  // Finished
  blink(LED, 500);
}