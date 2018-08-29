/* p11_5.c Deadband generation with center-aligned PWM

 * TPM0 uses MCGFLLCLK which is 41.94 MHz. The prescaler 
 * is set to divide by 16. The modulo register is set to 43703.
 * The timer is configured for center-aligned PWM.
 * channel 0 is configured for 60% duty cycle pulse low.
 * channel 1 is configured for 40% duty cycle pulse high.
 * This creates a 10% deadband between channel 0 high and
 * channel 1 high.
 */

#include <MKL25Z4.H>

int main (void) {
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTD->PCR[0] = 0x0400;     /* PTD0 used by TPM0 */
    PORTD->PCR[1] = 0x0400;     /* PTD1 used by TPM0 */

    SIM->SCGC6 |= 0x01000000;   /* enable clock to TPM0 */
    SIM->SOPT2 |= 0x01000000;   /* use MCGFLLCLK as timer counter clock */
    TPM0->SC = 0;               /* disable timer */
    TPM0->CONTROLS[0].CnSC = 0x20 | 0x04;   /* center-aligned, pulse low */
    TPM0->CONTROLS[1].CnSC = 0x20 | 0x08;   /* center-aligned, pulse high */
    TPM0->MOD = 43703;          /* Set up modulo register for 30Hz */
    TPM0->CONTROLS[0].CnV = 26221;  /* Set up channel value for 60% duty cycle */
    TPM0->CONTROLS[1].CnV = 17481;  /* Set up channel value for 40% duty cycle */
    TPM0->SC = 0x0C | 0x20; /* enable TPM0 with prescaler /16, center-aligned */
    
    while (1) {
    }
}