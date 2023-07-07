#pragma once

#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include <stdio.h>

// Only works with 11 khz audio

pwm_config __audio_config;
int __audio_slice, __audio_pin;

int __audio_position;
int __audio_start, __audio_end;
int __audio_length;
const uint8_t *__audio_data;

bool __audio_repeat;

void __audio_update_callback() {
  if (__audio_position == -1)
    __audio_position = __audio_start;
  pwm_clear_irq(pwm_gpio_to_slice_num(__audio_pin));
  if (__audio_position < __audio_end << 3) {
    // set pwm level
    // allow the pwm value to repeat for 8 cycles this is >>3
    pwm_set_gpio_level(__audio_pin, __audio_data[__audio_position >> 3]);
    __audio_position++;
  } else if (__audio_repeat)
    __audio_position = -1;
}

void audio_init(int pin) {
  if (clock_get_hz(clk_sys) / 1000 != 176000)
    set_sys_clock_khz(176000, true);

  __audio_pin = pin;

  gpio_set_function(__audio_pin, GPIO_FUNC_PWM);

  __audio_slice = pwm_gpio_to_slice_num(__audio_pin);

  pwm_clear_irq(__audio_slice);
  pwm_set_irq_enabled(__audio_slice, true);
  // set the handle function above
  irq_set_exclusive_handler(PWM_IRQ_WRAP, __audio_update_callback);
  irq_set_enabled(PWM_IRQ_WRAP, true);

  __audio_config = pwm_get_default_config();

  pwm_config_set_clkdiv(&__audio_config, 8.0f);
  pwm_config_set_wrap(&__audio_config, 250);
  pwm_init(__audio_slice, &__audio_config, true);

  pwm_set_gpio_level(__audio_pin, 0);
}

void audio_set(const uint8_t *data, int size) {
  __audio_data = data;
  __audio_length = size;

  __audio_position = -2;
}

void audio_play_range(int start, int end, bool repeat) {
  __audio_start = start;
  __audio_end = end;
  __audio_repeat = repeat;
  __audio_position = -1;
}

void audio_play(bool repeat) {
  return audio_play_range(0, __audio_length, repeat);
}

bool audio_is_finished() { return __audio_position > __audio_end; }