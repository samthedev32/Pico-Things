#include <stdio.h>
#include "pico/stdlib.h"

#include "sdcard.h"

int main()
{
    SDCard sd;

    SDCard_Mount(&sd);

    SDCard_Open(&sd, "hello_world.txt", FA_OPEN_APPEND | FA_WRITE);

    // SDCard_Write(&sd, "Hello from Pico (rp%i)\n", 2040);
    f_printf(&sd.fil, "hello from pico");

    SDCard_Close(&sd);

    SDCard_uMount(&sd);
}