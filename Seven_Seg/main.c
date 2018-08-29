/*
 * Sound the speaker at 440Hz
 * The speaker is connected to PTC 8.
 * Default clock 41.94MHz is used.
 */

#include "MKL25Z4.h"

void delayUs(int n);

int main(void)
{
    // enable PTC8 as output
    SIM->SCGC5 |= 0x800;        /* enable clock to Port C */
    PORTC->PCR[8] = 0x100;      /* make PTC8 pin as GPIO */
    PTC->PDDR |= 0x0100;        /* make PTC8 as output pin */

    for (;;)
    {
        PTC->PCOR = 0x0100;     /* turn off PTC8 */
        delayUs(1136);
        PTC->PSOR = 0x0100;     /* turn on PTC8 */
        delayUs(1136);
    }
}

// delay n microseconds (41.94MHz CPU clock)
void delayUs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 7; j++)
            {}  /* do nothing */
}