#pragma once

#include "phonetic.h"

void tts_phonetic_char(int pin, char c, int speed)
{
}

void tts_phonetic_string(int pin, char *s)
{
    while (*s)
    {
        // go throught each char
        *s++;
    }
}

void tts_char(int pin, char c)
{
}

void tts_string(int pin, char *s)
{
}