/* p7_4.c: Use DAC to generate sawtooth waveform

 * The DAC is initialized with no buffer and use software trigger,
 * so every write to the DAC data registers will change the analog output.
 * The loop count i is incremented by 0x0010 every loop. The 12-bit DAC
 * has the range of 0-0x0FFF. Divide 0x1000 by 0x0010 yields 0x0100 or 256.
 * The sawtooth has 256 steps and each step takes 1 ms. The period of the
 * waveform is 256 ms and the frequency is about 3.9 Hz.
 */

#include "MKL25Z4.h"

void DAC0_init(void);
void delayMs(int n);

int main (void) {
    int i;
    
	DAC0_init();    /* Configure DAC0 */
    
    while (1) {
        for (i = 0; i < 0x1000; i += 0x0010) {
            /* write value of i to DAC0 */
            DAC0->DAT[0].DATL = i & 0xff;       /* write low byte */
            DAC0->DAT[0].DATH = (i >> 8) & 0x0f;/* write high byte */
            delayMs(1);         /* delay 1ms */
        }
    }
}

void DAC0_init(void) {
	SIM->SCGC6 |= 0x80000000;   /* clock to DAC module */
	DAC0->C1 = 0;               /* disable the use of buffer */
	DAC0->C0 = 0x80 | 0x20;     /* enable DAC and use software trigger */
}

/* Delay n milliseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */
void delayMs(int n) {
    int i;
    int j;
    for(i = 0 ; i < n; i++)
        for (j = 0; j < 7000; j++) {}
}