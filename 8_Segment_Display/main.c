/* p2_9.c: Display number 25 on a 2-digit 7-segment LED.

 * Two common cathode 7-segment LEDs are used.
 * PTD0-6 are connected to segment A-G respectively.
 * PTE0 is used to control right digit (low for digit on).
 * PTE1 is used to control left digit (low for digit on).
 */

#include <MKL25Z4.H>

void delayMs(int n);

int main(void)
{    
    unsigned char digitPattern[] = 
        {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
        /*from Table 2-7 */

    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    SIM->SCGC5 |= 0x2000;       /* enable clock to Port E */
    PORTD->PCR[0] = 0x100;      /* make PTD0 pin as GPIO */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PORTD->PCR[2] = 0x100;      /* make PTD2 pin as GPIO */
    PORTD->PCR[3] = 0x100;      /* make PTD3 pin as GPIO */
    PORTD->PCR[4] = 0x100;      /* make PTD4 pin as GPIO */
    PORTD->PCR[5] = 0x100;      /* make PTD5 pin as GPIO */
    PORTD->PCR[6] = 0x100;      /* make PTD6 pin as GPIO */
    PTD->PDDR |= 0x7F;          /* make PTD6-0 as output pins */
    PORTE->PCR[0] = 0x100;      /* make PTE0 pin as GPIO */
    PORTE->PCR[1] = 0x100;      /* make PTE1 pin as GPIO */
    PTE->PDDR |= 0x03;          /* make PTE1-0 as output pin */

    for(;;)
    {
        PTD->PDOR = digitPattern[2];    /* drive pattern of 2 on the segments */
        PTE->PSOR = 0x01;               /* turn off right digit */
        PTE->PCOR = 0x02;               /* turn on left digit */
        /* delay 8 ms will result in 16 ms per loop or 62.5 Hz */
        delayMs(8);

        PTD->PDOR = digitPattern[5];    /* drive pattern of 5 on the segments */
        PTE->PCOR = 0x01;               /* turn on right digit */
        PTE->PSOR = 0x02;               /* turn off left digit */
        delayMs(8);       
    }
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