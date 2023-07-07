#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define ADC_CONVERT (3.3 / ((1 << 12) - 1))

int __mic_in;
float __mic_raw;

int __mic_size;
int __mic_cursor;
float *__mic_buffer;

struct repeating_timer __mic_timer;

bool __mic_update_callback(struct repeating_timer *t)
{
    adc_select_input(__mic_in);
    __mic_raw = adc_read();

    if (__mic_cursor >= __mic_size)
        __mic_cursor = 0;

    __mic_buffer[__mic_cursor] = __mic_raw;

    // Calculate frequency

    return true;
}

bool mic_start(int in, int buffer_size)
{
    if (in < 0 || in > 4)
        return false;

    __mic_in = in;
    __mic_size = buffer_size;
    if (__mic_buffer != NULL)
        free(__mic_buffer);

    __mic_buffer = (float *)malloc(sizeof(float) * buffer_size);
    for (int i = 0; i < buffer_size; i++)
        __mic_buffer[i] = 0;

    __mic_cursor = 0;

    adc_init();
    adc_gpio_init(26 + in);

    return add_repeating_timer_ms(1, __mic_update_callback, NULL, &__mic_timer);
}

bool mic_stop()
{
    return cancel_repeating_timer(&__mic_timer);
}

float mic_read()
{
    return __mic_raw;
}

float *mic_buffer()
{
    return __mic_buffer;
}