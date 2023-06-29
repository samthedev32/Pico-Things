#include <hardware/gpio.h>
#include <hardware/timer.h>
#include <hardware/uart.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <stdio.h>
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
}

// Receive Bluetooth Command/Message
void bluetooth_receive(bluetooth *bt, char **str, int length) {
  int i = 0;
  char c;
  while ((c = uart_getc(bt->uart)) != '\0') {
    *str[i] = c;
    c++;
    if (c >= length)
      break;
  }
}

// Send Bluetooth Message
void bluetooth_send(bluetooth *bt, const char *message) {
  uart_puts(bt->uart, message);
}
