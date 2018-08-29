/* p11_3.c Generate slow varying duty cycle PWM output

 * This program is setup similar to p11_2. 
 * 32kHz clock is used for timer counter clock so that
 * the pulse width change is visible by the blue LED.
 */

#include <MKL25Z4.H>
void delayMs(int n);

int main (void) {
    int pulseWidth = 0;
    
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTD->PCR[1] = 0x0400;     /* PTD1 used by TPM0 */

    SIM->SCGC6 |= 0x01000000;   /* enable clock to TPM0 */
    SIM->SOPT2 |= 0x03000000;   /* use 32KHz MCGIRCLK as timer counter clock */
    TPM0->SC = 0;               /* disable timer */
    TPM0->CONTROLS[1].CnSC = 0x20 | 0x08;   /* edge-aligned, pulse high */
    TPM0->MOD = 20000;          /* Set up modulo register for 30Hz */
    TPM0->SC = 0x08;            /* enable TPM0 */
    
    while (1) 
		{
        pulseWidth += 1000;
        if (pulseWidth > 20000)
            pulseWidth = 0;
        TPM0->CONTROLS[1].CnV = pulseWidth;
				delayMs(1000);
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