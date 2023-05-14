#include <stdio.h>
#include "pico/stdlib.h"

#include "terminal.h"

int blink10_cmd(const char *command)
{
    for (int i = 0; i < 10; i++)
    {
        CLI_Run("on");
        sleep_ms(100);
        CLI_Run("off");
        sleep_ms(100);
    }

    return 0;
}

int on_cmd(const char *command)
{
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    return 0;
}

int off_cmd(const char *command)
{
    gpio_put(PICO_DEFAULT_LED_PIN, 0);

    return 0;
}

int main()
{
    // Init LED Pin
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // Register Commands
    CLI_Register("blink10", blink10_cmd);
    CLI_Register("on", on_cmd);
    CLI_Register("off", off_cmd);

    while (true)
    {
        CLI_Run("on");
        sleep_ms(rand() % 700);
        CLI_Run("off");
        sleep_ms(rand() % 700);
    }
}