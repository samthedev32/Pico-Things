#pragma once

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Function Return Types
typedef enum {
  SDIO_SUCCESS,
  SDIO_UNKNOWN_ERROR,
  SDIO_INVALID_ENUM,
  SDIO_NO_CREATE_INFO
} SDIO_RETURN;
#define SDIO_SUCCESS 0

// Communication Mode
typedef enum { SDIO_MODE_1BIT, SDIO_MODE_4BIT } SDIO_MODE;

// SDIO Connection
typedef struct {
  // Pins
  struct {
    uint8_t CD;

    uint8_t CLK, CMD;
    uint8_t DAT[4];
  } pin;

} sdio_t;

// SDIO Create Info
typedef struct {
  // Connection Mode (1BIT/4BIT/SPI)
  SDIO_MODE mode;

  // Enable Software Pullups (CMD + DATA)
  bool software_pullup;

  // TODO: host/slave
} sdio_create_info_t;

// Create SDIO Connection
SDIO_RETURN sdio_create(sdio_t *sdio, sdio_create_info_t *createinfo);

/*

#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"

#include "st7789_lcd.pio.h"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define SERIAL_CLK_DIV 1.f

// Screen Rotations/Orientations
enum rotation { VERTICAL, HORIZONTAL, VERTICAL_OPPOSITE, HORIZONTAL_OPPOSITE };

// LCD
typedef struct lcd {
  uint sm;
  PIO pio;
  enum rotation orientation;

  int PIN_DIN;
  int PIN_CLK;
  int PIN_CS;
  int PIN_DC;
  int PIN_RESET;
  int PIN_BL;
} lcd;

// The Init Sequence for the ST7789 driver
static const uint16_t st7789_init_seq[] = {
    2, 1, 0x3a, 0x05,

    6, 20, 0xb2, 0x0c, 0x0c, 0x00, 0x33, 0x33, // Software reset
    2, 10, 0xb7, 0x35,                         // Exit sleep mode
    2, 2, 0xb, 0x1f,                           // Set colour mode to 16 bit
    2, 0, 0xc0, 0x2c, // Set MADCTL: row then column, refresh is bottom to
                      // top ????
    2, 0, 0xc2, 0x01, // CASET: column addresses from 0 to 240 (f0)
    2, 0, 0xc3, 0x12, // RASET: row addresses from 0 to 240 (f0)
    2, 2, 0xc4, 0x20, // Inversion on, then 10 ms delay (supposedly a
                      // hack?)
    2, 2, 0xc6, 0x0f, 3, 10, 0xd0, 0xa4, 0xa1, 2, 1, 0xd6, 0xa1, 15, 20, 0xe0,
    0xd0, 0x08, 0x11, 0x08, 0x0c, 0x15, 0x39, 0x33, 0x50, 0x36, 0x13, 0x14,
    0x29, 0x2d, 15, 20, 0xe0, 0xd0, 0x08, 0x10, 0x08, 0x06, 0x6, 0x39, 0x44,
    0x51, 0x0b, 0x16, 0x14, 0x2f, 0x31,

    1, 1, 0x21, 1, 1, 0x11, 1, 1, 0x29, 0};

// Set the ST7789 driver's DC and CS
static inline void st7789_set_dc_cs(lcd *screen, bool dc, bool cs) {
  sleep_us(1);
  gpio_put_masked((1u << screen->PIN_DC) | (1u << screen->PIN_CS),
                  !!dc << screen->PIN_DC | !!cs << screen->PIN_CS);
  sleep_us(1);
}

// Write a Command to the ST7789 driver
static inline void st7789_write_cmd(lcd *screen, const uint16_t *cmd,
                                    size_t count) {
  st7789_lcd_wait_idle(screen->pio, screen->sm);
  st7789_set_dc_cs(screen, 0, 0);
  st7789_lcd_put(screen->pio, screen->sm, *cmd++);
  if (count >= 2) {
    st7789_lcd_wait_idle(screen->pio, screen->sm);
    st7789_set_dc_cs(screen, 1, 0);
    for (size_t i = 0; i < count - 1; ++i)
      st7789_lcd_put(screen->pio, screen->sm, *cmd++);
  }
  st7789_lcd_wait_idle(screen->pio, screen->sm);
  st7789_set_dc_cs(screen, 1, 1);
}

// Init the ST7789 driver
static inline void st7789_init(lcd *screen, const uint16_t *init_seq) {
  const uint16_t *cmd = init_seq;
  while (*cmd) {
    st7789_write_cmd(screen, cmd + 2, *cmd);
    sleep_ms(*(cmd + 1) * 5);
    cmd += *cmd + 2;
  }
}

// Start the ST7789 driver's pixels
static inline void st7789_start_pixels(lcd *screen) {
  uint16_t cmd = 0x2c; // RAMWR
  st7789_write_cmd(screen, &cmd, 1);
  st7789_set_dc_cs(screen, 1, 0);
}

// Set LCD Backlight
void lcd_backlight(lcd *screen, int en) { gpio_put(screen->PIN_BL, en); }

// Attach LCD
void lcd_attach(lcd *screen) {
  stdio_init_all();
  uint offset = pio_add_program(screen->pio, &st7789_lcd_program);
  st7789_lcd_program_init(screen->pio, screen->sm, offset, screen->PIN_DIN,
                          screen->PIN_CLK, SERIAL_CLK_DIV);

  gpio_init(screen->PIN_CS);
  gpio_init(screen->PIN_DC);
  gpio_init(screen->PIN_RESET);
  gpio_init(screen->PIN_BL);
  gpio_set_dir(screen->PIN_CS, GPIO_OUT);
  gpio_set_dir(screen->PIN_DC, GPIO_OUT);
  gpio_set_dir(screen->PIN_RESET, GPIO_OUT);
  gpio_set_dir(screen->PIN_BL, GPIO_OUT);

  gpio_put(screen->PIN_CS, 1);
  gpio_put(screen->PIN_RESET, 1);

  st7789_init(screen, st7789_init_seq);

  lcd_backlight(screen, 1);
}

// Update LCD
void lcd_update(lcd *screen, uint16_t p[]) {
  st7789_start_pixels(screen);
  switch (screen->orientation) {
  case HORIZONTAL:
    for (int x = 0; x < SCREEN_HEIGHT; ++x) {
      for (int y = SCREEN_WIDTH - 1; y >= 0; --y) {
        st7789_lcd_put(screen->pio, screen->sm, p[x + y * SCREEN_HEIGHT] >> 8);
        st7789_lcd_put(screen->pio, screen->sm,
                       p[x + y * SCREEN_HEIGHT] & 0xff);
      }
    }
    break;

  case VERTICAL_OPPOSITE:
    for (int y = SCREEN_HEIGHT - 1; y >= 0; --y) {
      for (int x = SCREEN_WIDTH - 1; x >= 0; --x) {
        st7789_lcd_put(screen->pio, screen->sm, p[x + y * SCREEN_WIDTH] >> 8);
        st7789_lcd_put(screen->pio, screen->sm, p[x + y * SCREEN_WIDTH] & 0xff);
      }
    }
    break;

  case HORIZONTAL_OPPOSITE:
    for (int x = SCREEN_HEIGHT - 1; x >= 0; --x) {
      for (int y = 0; y < SCREEN_WIDTH; ++y) {
        st7789_lcd_put(screen->pio, screen->sm, p[x + y * SCREEN_HEIGHT] >> 8);
        st7789_lcd_put(screen->pio, screen->sm,
                       p[x + y * SCREEN_HEIGHT] & 0xff);
      }
    }
    break;

  default: // VERTICAL
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
      for (int x = 0; x < SCREEN_WIDTH; ++x) {
        st7789_lcd_put(screen->pio, screen->sm, p[x + y * SCREEN_WIDTH] >> 8);
        st7789_lcd_put(screen->pio, screen->sm, p[x + y * SCREEN_WIDTH] & 0xff);
      }
    }
    break;
  }
}
*/