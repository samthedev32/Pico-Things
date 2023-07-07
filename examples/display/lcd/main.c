#include "st7789.h"
#include "graphics.h"
#include <stdio.h>
#include "pico/stdlib.h"

const int LED_R = 6;
const int LED_G = 7;
const int LED_B = 8;

const int BUTTON_A = 12;
const int BUTTON_B = 13;
const int BUTTON_X = 14;
const int BUTTON_Y = 15;

lcd screen;
uint16_t pixels[240 * 320];

int main()
{
    screen.pio = pio0;
    screen.sm = 0;
    screen.orientation = HORIZONTAL;
    screen.PIN_DIN = 19;
    screen.PIN_CLK = 18;
    screen.PIN_CS = 17;
    screen.PIN_DC = 16;
    screen.PIN_RESET = 21;
    screen.PIN_BL = 20;
    lcd_attach(&screen);

    gpio_init(LED_R);
    gpio_init(LED_G);
    gpio_init(LED_B);

    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_set_dir(LED_B, GPIO_OUT);

    gpio_put(LED_R, 1);
    gpio_put(LED_G, 1);
    gpio_put(LED_B, 1);

    gpio_set_function(BUTTON_A, GPIO_FUNC_SIO);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_set_function(BUTTON_B, GPIO_FUNC_SIO);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
    gpio_set_function(BUTTON_X, GPIO_FUNC_SIO);
    gpio_set_dir(BUTTON_X, GPIO_IN);
    gpio_pull_up(BUTTON_X);
    gpio_set_function(BUTTON_Y, GPIO_FUNC_SIO);
    gpio_set_dir(BUTTON_Y, GPIO_IN);
    gpio_pull_up(BUTTON_Y);

    int w = 320;
    int h = 240;

    int pos_x = w / 2 - 10;
    int pos_y = h / 2 - 10;
    int speed = 2;
    int dir_x = speed;
    int dir_y = speed;

    while (1)
    {
        graphics_fill(pixels, w * h, rgb_to_hex(0, 255, 0));
        graphics_rect(pixels, w, h, pos_x, pos_y, 20, 20, rgb_to_hex(0, 150, 0));

        graphics_string(pixels, w, h, "MOUNTAIN", 50, 50, getStringWidth("MOUNTAIN", 50), 50, rgb_to_hex(0, 150, 0));
        graphics_string(pixels, w, h, "DEW", 60, 50, getStringWidth("DEW", 80), 80, rgb_to_hex(255, 0, 0));

        lcd_update(&screen, pixels);

        pos_x += dir_x;
        pos_y += dir_y;

        if (pos_x < 0)
            dir_x = speed;
        if (pos_x > 220)
            dir_x = -speed;

        if (pos_y < 0)
            dir_y = speed;
        if (pos_y > 300)
            dir_y = -speed;

        pos_x += dir_x;
        pos_y += dir_y;
    }
}