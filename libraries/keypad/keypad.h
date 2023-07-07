#pragma once

#include <stdlib.h>
#include "pico/stdlib.h"

// A Basic X by Y Keypad
typedef struct keypad
{
    int pins;
    int *pin;

    char *key;

    bool *active;

    int w, h;
} keypad;

/**
 * @brief Initalize a Keypad
 *
 * @param kp The Keypad to Init;
 *
 * @param w The Width of the Keypad
 * @param h The Height of the Keypad
 *
 * @param pins The Number of pins in the Keypad
 * @param pin The Array of Pins
 */
void keypad_init(keypad *kp, int w, int h, int pins, int pin[])
{
    // TODO: va_list the pins
    kp->w = w;
    kp->h = h;
    kp->pins = pins;
    kp->pin = (int *)malloc(sizeof(int) * pins);

    kp->key = (char *)malloc(sizeof(char) * w * h);
    kp->active = (bool *)malloc(sizeof(bool) * w * h);

    for (int i = 0; i < pins; i++)
        kp->pin[i] = pin[i];

    for (int i = 0; i < h; i++)
    {
        gpio_init(kp->pin[i]);
        gpio_set_dir(kp->pin[i], GPIO_OUT);
        gpio_put(kp->pin[i], 0);
    }

    for (int i = h; i < h + w; i++)
    {
        gpio_init(kp->pin[i]);
        gpio_set_dir(kp->pin[i], GPIO_IN);
    }
}

/**
 * @brief Set Key Characters
 *
 * @param kp The Keypad
 * @param key The Key Array
 */
void keypad_setkeys(keypad *kp, char key[])
{
    int keys = kp->w * kp->h;
    for (int i = 0; i < keys; i++)
        kp->key[i] = key[i];
}

/**
 * @brief Update The Keypad
 *
 * @param kp The Keypad
 */
void keypad_update(keypad *kp)
{
    for (int y = 0; y < kp->h; y++)
    {
        gpio_put(kp->pin[y], 1);

        for (int x = 0; x < kp->w; x++)
        {
            if (gpio_get(kp->pin[kp->h + x]))
                kp->active[kp->w * y + x] = true;
            else
                kp->active[kp->w * y + x] = false;
        }

        gpio_put(kp->pin[y], 0);
    }
}

/**
 * @brief Get Position's State
 *
 * @param kp The Keypad
 *
 * @param x The X coordinate
 * @param y The Y coordinate
 */
bool keypad_read(keypad *kp, int x, int y)
{
    return kp->active[y * kp->w + x];
}

/**
 * @brief Get Character's State
 *
 * @param c The Character
 */
bool keypad_readc(keypad *kp, char c)
{
    int s = kp->w * kp->h;
    for (int i = 0; i < s; i++)
    {
        if (kp->key[i] == c)
            return kp->active[i];
    }
}