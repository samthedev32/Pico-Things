#include "slcd.h"

int main(void)
{
    slcd d;
    slcd_init(&d, 16, 2, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    slcd_prints(&d, "Hello, world!");

    while (1)
    {
        sleep_ms(10);
    }
}