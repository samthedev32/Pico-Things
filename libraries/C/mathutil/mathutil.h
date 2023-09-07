#pragma once

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef M_E
double M_E = 2.7182818284590452354;
#endif

#ifndef M_PI
double M_PI = 3.141592653;
#endif

// A Basic Sigmoid Function
double sig(double x) { return 1 / (1 + (double)pow((double)M_E, (double)-x)); }

// Get the System Uptime
// uint64_t time(bool us) {
//   if (us)
//     return to_us_since_boot(get_absolute_time());
//   return to_ms_since_boot(get_absolute_time());
// }

// Get a Char* 's Length
int len(char *s) {
  int i = 0;
  while (*s) {
    i++;
    *s++;
  }
  return i;
}

// Get The Higher Number
int max(int a, int b) {
  if (a > b)
    return a;
  return b;
}

// Get The Lower Number
int min(int a, int b) {
  if (a < b)
    return a;
  return b;
}

// Convert RGB to HEX
uint16_t rgb_to_hex(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) |
         ((b & 0b11111000) >> 3);
}