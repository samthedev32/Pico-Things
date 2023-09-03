#include <sdio.h>

#include "hardware/gpio.h"

SDIO_RETURN sdio_create(sdio_t *sdio, sdio_create_info_t *createinfo) {
  if (!createinfo)
    return SDIO_NO_CREATE_INFO;

  gpio_init(sdio->pin.CD);

  gpio_init(sdio->pin.CLK);
  gpio_init(sdio->pin.CMD);

  for (int i = 0; i < 4; i++)
    gpio_init(sdio->pin.DAT[i]);

  gpio_set_dir(sdio->pin.CD, GPIO_IN);
  gpio_set_dir(sdio->pin.CD, GPIO_IN);

  gpio_set_dir(sdio->pin.CD, GPIO_IN);
  gpio_set_dir(sdio->pin.CD, GPIO_IN);

  for (int i = 0; i < 4; i++)
    gpio_set_dir(sdio->pin.DAT[i], GPIO_OUT);

  gpio_put(sdio->, 0);

  switch (createinfo->mode) {
  case SDIO_MODE_1BIT:
    break;

  case SDIO_MODE_4BIT:
    break;

  default:
    return SDIO_INVALID_ENUM;
    break;
  }

  return SDIO_SUCCESS;
}