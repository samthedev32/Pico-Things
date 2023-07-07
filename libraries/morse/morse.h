#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "table.h"

// Put out a Letter on a Pin (in morse)
void morse_put_letter(uint pin, const char *pattern)
{
    for (; *pattern; ++pattern)
    {
        gpio_put(pin, 1);

        if (*pattern == '.')
            sleep_ms(MORSE_LEN_MS * MORSE_LEN_DOT);
        else
            sleep_ms(MORSE_LEN_MS * MORSE_LEN_DASH);

        gpio_put(pin, 0);
        sleep_ms(MORSE_LEN_MS * MORSE_LEN_PARTS);
    }
    sleep_ms(MORSE_LEN_MS * MORSE_LEN_LETTER);
}

// Put out a String on a Pin (in morse)
void morse_put_string(uint pin, const char *str)
{
    for (; *str; ++str)
    {
        if (*str >= 'A' && *str <= 'Z')
        {
            morse_put_letter(pin, morse_letters[*str - 'A']);
        }
        else if (*str >= 'a' && *str <= 'z')
        {
            morse_put_letter(pin, morse_letters[*str - 'a']);
        }
        else if (*str >= '0' && *str <= '9')
        {
            morse_put_letter(pin, morse_numbers[*str - '0']);
        }
        else if (*str == ' ')
        {
            sleep_ms(MORSE_LEN_MS * MORSE_LEN_WORD);
        }
    }
}

// Get Letter on a Pin
// TODO
char morse_get_letter(uint pin)
{
    return ' ';
}