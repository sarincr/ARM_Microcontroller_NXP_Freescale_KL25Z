/* p7_5.c: Use DAC to generate sine wave with look-up table

 * This program uses a pre-calculated lookup table to generate a
 * sine wave output through DAC.
 */

#include "MKL25Z4.h"

void DAC0_init(void);
void delayMs(int n);

int main (void) {
    int i;
    const static int sineWave[] = 
        {1862, 2793, 3474, 3724, 3474, 2793,
         1862,  931,  249,    0,  249,  931};

    DAC0_init();                    /* Configure DAC0 */
    
    while (1) {
        for (i = 0; i < 12; i++) {
            /* write value to DAC0 */
            DAC0->DAT[0].DATL = sineWave[i] & 0xff;       /* write low byte */
            DAC0->DAT[0].DATH = (sineWave[i] >> 8) & 0x0f;/* write high byte */
            delayMs(1);         /* delay 1ms */
        }
    }
}

void DAC0_init(void) {
	SIM->SCGC6 |= 0x80000000;       /* clock to DAC module */
	DAC0->C1 = 0;                   /* disable the use of buffer */
	DAC0->C0 = 0x80 | 0x20;         /* enable DAC and use software trigger */
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