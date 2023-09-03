#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint8_t DT, SCK;
} HX711;

unsigned long hx711_read(HX711 hx) {
  unsigned long Count;
  unsigned char i;

  gpio_set_dir(hx.DT, GPIO_OUT);

  gpio_put(hx.DT, 1);
  gpio_put(hx.SCK, 0);

  gpio_set_dir(hx.DT, GPIO_IN);

  Count = 0;
  while (gpio_get(hx.DT))
    ;

  for (i = 0; i < 24; i++) {
    gpio_put(hx.SCK, 1);
    Count = Count << 1;
    gpio_put(hx.SCK, 0);
    if (gpio_get(hx.DT))
      Count++;
  }

  gpio_put(hx.SCK, 1);
  Count = Count ^ 0x800000;
  gpio_put(hx.SCK, 0);

  return (Count);
}

// ASM:
/*-------------------------------------------------------------------
Call from ASM: LCALL ReaAD
Call from C: extern unsigned long ReadAD(void);
.
.
unsigned long data;
data=ReadAD();
.
.
----------------------------------------------------------------------/
PUBLIC ReadAD HX711ROM segment code rseg HX711ROM sbit ADDO = P1 .5;
sbit ADSK = P0 .0;
/*--------------------------------------------------
OUT: R4, R5, R6, R7 R7=>LSB
---------------------------------------------------/
ReadAD : CLR ADSK      // AD Enable（PD_SCK set low）
             SETB ADDO // Enable 51CPU I/0
                 JB ADDO,
         $ // AD conversion completed?
             MOV R4,
         #24 ShiftOut : SETB ADSK        // PD_SCK set high（positive pulse）
                            NOP CLR ADSK // PD_SCK set low
                                MOV C,
                        ADDO // read on bit
                            XCH A,
                        R7 // move data
                            RLC A XCH A,
                        R7 XCH A,
                        R6 RLC A XCH A,
                        R6 XCH A,
                        R5 RLC A XCH A,
                        R5 DJNZ R4,
                        ShiftOut // moved 24BIT?
                                SETB ADSK NOP CLR ADSK RET END
                                */