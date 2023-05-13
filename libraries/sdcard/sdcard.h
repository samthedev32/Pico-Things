#include "f_util.h"
#include "ff.h"
#include "pico/stdlib.h"
#include "rtc.h"

#include "hw_config.h"

#include <stdarg.h>

typedef struct
{
    bool mounted;
    sd_card_t *sd;

    bool opened;
    FIL fil;
} SDCard;

// Mount SD Card
int SDCard_Mount(SDCard *sdcard)
{
    // Exit if NULL / Mounted
    if (sdcard == NULL || sdcard->mounted)
        return -1;

    // Reset Variables
    sdcard->mounted = false;
    sdcard->sd = NULL;

    sdcard->opened = false;

    // Get SD Card
    sdcard->sd = sd_get_by_num(0);

    // Mount SD Card
    FRESULT fr = f_mount(&sdcard->sd->fatfs, sdcard->sd->pcName, 1);

    if (fr != FR_OK)
        return -2;

    sdcard->mounted = true;

    return 0;
}

// Unmount SD Card
int SDCard_uMount(SDCard *sdcard)
{
    if (!sdcard->mounted)
        return 0;

    f_unmount(sdcard->sd->pcName);

    return 0;
}

// File access mode and open method flags:
// FA_READ
// FA_WRITE
// FA_OPEN_EXISTING
// FA_CREATE_NEW
// FA_CREATE_ALWAYS
// FA_OPEN_ALWAYS
// FA_OPEN_APPEND

// Open File from SD Card
int SDCard_Open(SDCard *sdcard, const char *filename, BYTE mode)
{
    if (sdcard->opened)
        return -1;

    FRESULT fr = f_open(&sdcard->fil, filename, mode);

    if (fr != FR_OK && fr != FR_EXIST)
        return -1;

    sdcard->opened = true;

    return 0;
}

// Close File from SD Card
int SDCard_Close(SDCard *sdcard)
{
    if (!sdcard->opened)
        return 0;

    FRESULT fr = f_close(&sdcard->fil);

    if (fr != FR_OK)
    {
        printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
    }

    sdcard->opened = false;

    return 0;
}

// Write to Currently Open File on SD Card
int SDCard_Write(SDCard *sdcard, const TCHAR *fmt, ...)
{
    if (!sdcard->opened)
        return -1;

    va_list arp;
    va_start(arp, fmt);

    int r = f_vprintf(sdcard->fil, fmt, arp);

    va_end(arp);

    return r;
}