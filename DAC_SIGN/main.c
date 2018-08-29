/* p7_6.c: Use DAC to generate sine wave

 * The program calculates the lookup table to generate
 * sine wave. 
 */

#include "MKL25Z4.h"
#include <math.h>

void DAC0_init(void);
#define WAVEFORM_LENGTH 256
int sinewave[WAVEFORM_LENGTH];

int main(void) {
    void delayMs(int n);
    int i;
    float fRadians;
    const float M_PI = 3.1415926535897;

    /* construct data table for a sine wave */
    fRadians = ((2 * M_PI) / WAVEFORM_LENGTH);
    
    for (i = 0; i < WAVEFORM_LENGTH; i++) {
        sinewave[i] = 2047 * (sinf(fRadians * i) + 1);
    }
    
	DAC0_init();                    /* Configure DAC0 */

    while (1) {
        for (i = 0; i < WAVEFORM_LENGTH; i++) {
            /* write value to DAC0 */
            DAC0->DAT[0].DATL = sinewave[i] & 0xff;       /* write low byte */
            DAC0->DAT[0].DATH = (sinewave[i] >> 8) & 0x0f;/* write high byte */
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