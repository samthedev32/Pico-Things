#pragma once

#include <stdlib.h>
#include "pico/stdlib.h"
#include "sd_card.h"
#include "ff.h"

#include "config.h"

typedef struct sd
{
  FATFS fs;
  FIL fil;
} sd;

sd *sd_init()
{
  sd *card = (sd *)malloc(sizeof(sd));

  sd_init_driver();

  return card;
}

bool sd_mount(sd *card)
{
  if (f_mount(&card->fs, "0:", 1) != FR_OK)
    return false;
  return true;
}

bool sd_unmount()
{
  f_unmount("0:");
  return true;
}

bool file_open(sd *card, char *path, BYTE mode)
{
  if (f_open(&card->fil, path, mode) != FR_OK)
    return false;
  return true;
}

bool file_close(sd *card)
{
  if (f_close(&card->fil) != FR_OK)
    return false;
  return true;
}

bool file_write(sd *card, char *data)
{
  if (f_printf(&card->fil, data) != FR_OK)
    return false;
  return true;
}

TCHAR *file_readln(sd *card, char *line, int len)
{
  return f_gets(line, len, &card->fil);
}