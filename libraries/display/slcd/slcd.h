#pragma once

#include "mathutil.h"
#include "pico/stdlib.h"

typedef struct slcd {
  int pin[11];
  int rs, rw, e;

  int w, h;
} slcd;

void slcd_write(slcd *d, bool rs, bool rw, bool D7, bool D6, bool D5, bool D4,
                bool D3, bool D2, bool D1, bool D0) {
  gpio_put(d->pin[8], rs);
  gpio_put(d->pin[9], rw); // Set R/W to Write
  gpio_put(d->pin[10], 0); // Set E to false

  gpio_put(d->pin[0], D0);
  gpio_put(d->pin[1], D1);
  gpio_put(d->pin[2], D2);
  gpio_put(d->pin[3], D3);
  gpio_put(d->pin[4], D4);
  gpio_put(d->pin[5], D5);
  gpio_put(d->pin[6], D6);
  gpio_put(d->pin[7], D7);

  gpio_put(d->pin[10], 1); // Set E to true
  sleep_ms(2);
  gpio_put(d->pin[10], 0); // Set E to false

  for (int i = 0; i < 11; i++) {
    gpio_put(d->pin[i], 0);
  }
}

static char slcd_chart[16][16] = {{' ', ' ', ' ', '0', ' ', 'P', ' ', 'p', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '!', '1', 'A', 'Q', 'a', 'q', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '"', '2', 'B', 'R', 'b', 'r', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '#', '3', 'C', 'S', 'c', 's', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '$', '4', 'D', 'T', 'd', 't', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '%', '5', 'E', 'U', 'e', 'u', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '&', '6', 'F', 'V', 'f', 'v', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '\'', '7', 'G', 'W', 'g', 'w', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '(', '8', 'H', 'X', 'h', 'x', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', ')', '9', 'I', 'Y', 'i', 'y', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '*', ':', 'J', 'Z', 'j', 'z', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '+', ';', 'K', '[', 'k', '{', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', ',', '<', 'L', ' ', 'l', '|', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '-', '=', 'M', ']', 'm', '}', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '.', '>', 'N', '^', 'n', ' ', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                  {' ', ' ', '/', '?', 'O', '_', 'o', ' ', ' ',
                                   ' ', ' ', ' ', ' ', ' ', ' ', ' '}};

void itobin(int i, int *b0, int *b1, int *b2, int *b3) {
  switch (i) {
  case 0:
    *b0 = 0;
    *b1 = 0;
    *b2 = 0;
    *b3 = 0;
    break;

  case 1:
    *b0 = 1;
    *b1 = 0;
    *b2 = 0;
    *b3 = 0;
    break;

  case 2:
    *b0 = 0;
    *b1 = 1;
    *b2 = 0;
    *b3 = 0;
    break;

  case 3:
    *b0 = 1;
    *b1 = 1;
    *b2 = 0;
    *b3 = 0;
    break;

  case 4:
    *b0 = 0;
    *b1 = 0;
    *b2 = 1;
    *b3 = 0;
    break;

  case 5:
    *b0 = 1;
    *b1 = 0;
    *b2 = 1;
    *b3 = 0;
    break;

  case 6:
    *b0 = 0;
    *b1 = 1;
    *b2 = 1;
    *b3 = 0;
    break;

  case 7:
    *b0 = 1;
    *b1 = 1;
    *b2 = 1;
    *b3 = 0;
    break;

  case 8:
    *b0 = 0;
    *b1 = 0;
    *b2 = 0;
    *b3 = 1;
    break;

  case 9:
    *b0 = 1;
    *b1 = 0;
    *b2 = 0;
    *b3 = 1;
    break;

  case 10:
    *b0 = 0;
    *b1 = 1;
    *b2 = 0;
    *b3 = 1;
    break;

  case 11:
    *b0 = 1;
    *b1 = 1;
    *b2 = 0;
    *b3 = 1;
    break;

  case 12:
    *b0 = 0;
    *b1 = 0;
    *b2 = 1;
    *b3 = 1;
    break;

  case 13:
    *b0 = 1;
    *b1 = 0;
    *b2 = 1;
    *b3 = 1;
    break;

  case 14:
    *b0 = 0;
    *b1 = 1;
    *b2 = 1;
    *b3 = 1;
    break;

  case 15:
    *b0 = 1;
    *b1 = 1;
    *b2 = 1;
    *b3 = 1;
    break;
  }
}

void slcd_clear(slcd *d) { slcd_write(d, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1); }

void slcd_display(slcd *d, bool display, bool cursor, bool blink) {
  slcd_write(d, 0, 0, 0, 0, 0, 0, 1, display, cursor, blink);
}

void slcd_init(slcd *d, int w, int h, int RS, int RW, int E, int D0, int D1,
               int D2, int D3, int D4, int D5, int D6, int D7) {
  d->pin[0] = D0;
  d->pin[1] = D1;
  d->pin[2] = D2;
  d->pin[3] = D3;
  d->pin[4] = D4;
  d->pin[5] = D5;
  d->pin[6] = D6;
  d->pin[7] = D7;

  d->pin[8] = RS;
  d->pin[9] = RW;
  d->pin[10] = E;

  d->w = w;
  d->h = h;

  for (int i = 0; i < 11; i++) {
    gpio_init(d->pin[i]);
    gpio_set_dir(d->pin[i], GPIO_OUT);
    gpio_put(d->pin[i], 0);
  }

  slcd_write(d, 0, 0, 0, 0, 1, 1, 1, 0, 0,
             0);            // Set 8 bit mode, 2 lines and 5*8 dot characters
  slcd_display(d, 1, 0, 0); // Turn on display, turn off cursor and blinking
  slcd_write(d, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0); // Set mode to increment
}

void slcd_printc(slcd *d, char c) {
  int data[8];

  for (int x = 0; x < 16; x++) {
    for (int y = 0; y < 16; y++) {
      if (slcd_chart[x][y] == c) {
        itobin(x, &data[7], &data[6], &data[5], &data[4]);
        itobin(y, &data[3], &data[2], &data[1], &data[0]);
      }
    }
  }

  slcd_write(d, 1, 0, data[0], data[1], data[2], data[3], data[4], data[5],
             data[6], data[7]);
}

void slcd_prints(slcd *d, char *s) {
  int size = strlen(s);

  for (int i = 0; i < size; i++)
    slcd_printc(d, s[i]);
}

void slcd_printi(slcd *d, int n) {
  char s[10];

  for (int i = 0; i < 10; i++)
    s[i] = ' ';

  itoa(n, s, 10);

  if (n >= 0)
    slcd_prints(d, s);
  else {
    slcd_printc(d, '-');
    slcd_prints(d, s);
  }
}