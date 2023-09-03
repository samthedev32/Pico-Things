#include <sdio.h>

int main() {
  sdio_t sdio;
  sdio_create_info_t createInfo = {};
  createInfo.mode = SDIO_MODE_1BIT;

  if (sdio_create(&sdio, &createInfo) != SDIO_SUCCESS)
    return 1;

  while (1)
    ;
}
