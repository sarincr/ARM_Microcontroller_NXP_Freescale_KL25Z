/* p11_2.c Generate 60Hz with varying duty cycle PWM output

 * This program is setup identical to p11_1. But in the 
 * infinite loop, the CnV register value is incremented 
 * by 437 (1%) every 20ms. Because the LED is low active,
 * the longer the duty cycle results in lower light intensity.
 */

#include <MKL25Z4.H>
void delayMs(int n);

int main (void) 
	{
    int pulseWidth = 0;
    
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTD->PCR[1] = 0x0400;     /* PTD1 used by TPM0 */

    SIM->SCGC6 |= 0x01000000;   /* enable clock to TPM0 */
    SIM->SOPT2 |= 0x01000000;   /* use MCGFLLCLK as timer counter clock */
    TPM0->SC = 0;               /* disable timer */
    TPM0->CONTROLS[1].CnSC = 0x20 | 0x08;   /* edge-aligned, pulse high */
    TPM0->MOD = 48000;          /* Set up modulo register for 60 kHz */
    TPM0->CONTROLS[1].CnV = 14568;  /* Set up channel value for 33% dutycycle */
    TPM0->SC = 0x0C;            /* enable TPM0 with prescaler /16 */
    
    while (1) {
        pulseWidth = pulseWidth+480;
        if (pulseWidth > 48000)
            pulseWidth = 0;
        TPM0->CONTROLS[1].CnV = pulseWidth;
        delayMs(20);
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