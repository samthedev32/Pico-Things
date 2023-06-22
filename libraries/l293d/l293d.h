#include <pico/stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#define L293D_FULL_STEP_SEQUENCES 4
#define STEPPER_HALF_STEP_SEQUENCES STEPPER_FULL_STEP_SEQUENCES * 2

typedef struct {
  int ena, enb;
  int a[2], b[2];
} l293d;

void l293d_init(l293d *motor) {
  gpio_init(motor->ena);
  gpio_init(motor->enb);

  gpio_init(motor->a[0]);
  gpio_init(motor->a[1]);

  gpio_init(motor->b[0]);
  gpio_init(motor->b[1]);

  gpio_set_dir(motor->ena, GPIO_OUT);
  gpio_set_dir(motor->enb, GPIO_OUT);

  gpio_set_dir(motor->a[0], GPIO_OUT);
  gpio_set_dir(motor->a[1], GPIO_OUT);

  gpio_set_dir(motor->b[0], GPIO_OUT);
  gpio_set_dir(motor->b[1], GPIO_OUT);

  gpio_put(motor->ena, 0);
  gpio_put(motor->enb, 0);
}

void l293d_enable(l293d *motor, int a, int b) {
  gpio_put(motor->ena, a);
  gpio_put(motor->enb, b);
}

void l293d_set(l293d *motor, int a, int b) {
  gpio_put(motor->a[0], 1);
  gpio_put(motor->a[1], 0);
  gpio_put(motor->b[0], 1);
  gpio_put(motor->b[1], 0);
}