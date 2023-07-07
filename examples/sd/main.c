#include "sd.h"

int main()
{
    sd *card = sd_init();

    sd_mount(card);

    file_open(card, "test.txt", FA_WRITE | FA_CREATE_ALWAYS);

    file_write(card, "Hello from the Pico!\n");

    file_close(card);

    sd_unmount();

    gpio_init(4);
    gpio_set_dir(4, GPIO_OUT);
    gpio_put(4, 1);
    sleep_ms(100);
    gpio_put(4, 0);

    while (1)
        ;
}
