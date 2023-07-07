#include <hardware/gpio.h>
#include <hardware/timer.h>
#include <hardware/uart.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  uart_inst_t *uart;
  uint8_t TX, RX;
} bluetooth;

// Get If new Bluetooth Message is Available
uint8_t bluetooth_available(bluetooth *bt) {
  return uart_is_enabled(bt->uart) && uart_is_readable(bt->uart);
}

// Initialize Bluetooth Module
void bluetooth_init(bluetooth *bt) {
  // Init UART
  uart_init(bt->uart, 9600);
  gpio_set_function(bt->TX, GPIO_FUNC_UART);
  gpio_set_function(bt->RX, GPIO_FUNC_UART);
  uart_set_format(bt->uart, 8, 1, UART_PARITY_NONE);
}

// Receive Bluetooth Command/Message
void bluetooth_receive(bluetooth *bt, char **data) {
  size_t buffer_size = 32;
  size_t len = 0;

  *data = (char *)malloc(buffer_size);

  while (uart_is_readable(bt->uart)) {
    char c = uart_getc(bt->uart);

    // Exit if (msg == '\0')
    if (c == '\0') {
      (*data)[len] = c;
      break;
    }

    // Add Character
    (*data)[len] = c;
    (*data)[len + 1] = '\0';
    len++;

    // Expand Buffer (if needed)
    if (len + 1 >= buffer_size) {
      buffer_size += 32;
      *data = (char *)realloc(*data, buffer_size);
    }

    // Sleep, so the BT Module can catch up
    sleep_ms(5);
  }
}

// Send Bluetooth Message
void bluetooth_send(bluetooth *bt, const char *message) {
  uart_puts(bt->uart, message);
}
