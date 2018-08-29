/* p11_1.c Generate 30Hz 40% center-aligned PWM

 * TPM0 uses MCGFLLCLK which is 41.94 MHz.
 * The prescaler is set to divide by 16.
 * The modulo register is set to 43703 and the CnV
 * register is set to 17481. TPM0 channel 1 is
 * configured to be center-aligned pulse high.
 */

#include <MKL25Z4.H>

int main (void) 
	{
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTD->PCR[1] = 0x0400;     /* PTD1 used by TPM0 */

    SIM->SCGC6 |= 0x01000000;   /* enable clock to TPM0 */
    SIM->SOPT2 |= 0x01000000;   /* use MCGFLLCLK as timer counter clock */
    TPM0->SC = 0;               /* disable timer */
    TPM0->CONTROLS[1].CnSC = 0x20 | 0x08;   /* center-aligned, pulse high */
    TPM0->MOD = 41940;          /* Set up modulo register for 1 kHz */
    TPM0->CONTROLS[1].CnV = 17481;  /* Set up channel value for 40% duty cycle */
    TPM0->SC = 0x0C | 0x20; /* enable TPM0 with prescaler /16, center-aligned */
    
    while (1) {
    }
}