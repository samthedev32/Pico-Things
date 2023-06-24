#include <hardware/gpio.h>
#include <hardware/timer.h>
#include <hardware/uart.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <string.h>

// Max Size of the Responses (size)
#define BLUETOOTH_MAX_RESPONSE_SIZE 256

// Command Response Timeout (s)
#define BLUETOOTH_RESPONSE_TIMEOUT 1

// Command Response Check Frequency (ms)
#define BLUETOOTH_RESPONSE_CHECK_FREQUENCY 100

// Docs:
// https://components101.com/sites/default/files/component_datasheet/HC-05%20Datasheet.pdf

typedef struct {
  uart_inst_t *uart;
  uint8_t TX, RX;

  uint baudrate;
} bluetooth;

// Initialize Bluetooth Module
int bluetooth_init(bluetooth *bt) {
  // Init UART
  uart_init(bt->uart, bt->baudrate);
  gpio_set_function(bt->TX, GPIO_FUNC_UART);
  gpio_set_function(bt->RX, GPIO_FUNC_UART);

  // Verify Connection
  uart_puts(bt->uart, "AT");

  uint64_t timeout = time_us_64() + BLUETOOTH_RESPONSE_TIMEOUT * 1000000;
  while (!uart_is_readable(bt->uart)) {
    if (time_us_64() > timeout)
      return 1;
    sleep_ms(BLUETOOTH_RESPONSE_CHECK_FREQUENCY);
  }

  // Read Response
  char response[BLUETOOTH_MAX_RESPONSE_SIZE];

  int i = 0;
  char c;
  while ((c = uart_getc(bt->uart)) != '\0') {
    response[i] = c;
    c++;
  }

  if (!strcmp(response, "OK"))
    return 0;

  return 2;
}

// Receive Bluetooth Command/Message
void bluetooth_receive(bluetooth *bt, char *str) {
  int i = 0;
  char c;
  while ((c = uart_getc(bt->uart)) != '\0') {
    str[i] = c;
    c++;
  }
}

// Send Bluetooth Command/Message
void bluetooth_command(bluetooth *bt, const char *command) {
  uart_puts(bt->uart, command);

  // Get Response
  //   uint64_t timeout = time_us_64() + 10000;
  //   while (!uart_is_readable(bt->uart) && time_us_64() < timeout)
  //     sleep_ms(100);

  //   if (uart_is_readable(bt->uart)) {
  //     char response[BLUETOOTH_MAX_RESPONSE_SIZE];
  //     char c;
  //     int i = 0;
  //     while ((c = uart_getc(bt->uart)) != '\0') {
  //       {
  //         if (i < BLUETOOTH_MAX_RESPONSE_SIZE)
  //           response[i] = c;
  //         i++;
  //       }
  //     }
  //   }
}
