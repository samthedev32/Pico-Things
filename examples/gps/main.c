#include <stdio.h>
#include "pico/stdlib.h"

#include "gps.h"

int main()
{
    stdio_init_all();

    GPS gps;
    setup_gps();

    while (true)
    {
        check_gps(&gps);

        printf("Sats: %i\n", gps.satellites);
    }
}