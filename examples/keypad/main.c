#include "keypad.h"

int main()
{
    keypad kp;
    int pins[] = {16, 17, 18, 19, 20, 21, 22, 23};
    keypad_init(&kp, 4, 4, 8, pins);

    while (1)
    {
        keypad_update(&kp);

        if (kp.active[1])
            sleep_ms(1000);

        sleep_ms(100);
    }
}