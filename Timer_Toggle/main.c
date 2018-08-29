/* p5_5.c Toggling blue LED using TPM0 delay (prescaler)

 * This program uses TPM0 to generate maximal delay to
 * toggle the blue LED.
 * MCGFLLCLK (41.94 MHz) is used as timer counter clock.
 * Prescaler is set to divided by 128 and the Modulo register
 * is set to 65,535. The timer counter overflows at
 * 41.94 MHz / 128 / 65,536 = 5.0 Hz
 * 
 * The blue LED is connected to PTD1.
 */

#include <MKL25Z4.H>

int main (void) {
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PTD->PDDR |= 0x02;          /* make PTD1 as output pin */
    
    SIM->SCGC6 |= 0x01000000;   /* enable clock to TPM0 */
    SIM->SOPT2 |= 0x01000000;   /* use MCGFLLCLK as timer counter clock */
    
    TPM0->SC = 0;               /* disable timer while configuring */
    TPM0->SC = 0x07;            /* prescaler /128 */
    TPM0->MOD = 0xFFFF;         /* max modulo value */
    TPM0->SC |= 0x80;           /* clear TOF */
    TPM0->SC |= 0x08;           /* enable timer free-running mode */
    
    while (1) {
        while((TPM0->SC & 0x80) == 0) { } /* wait until the TOF is set */
        TPM0->SC |= 0x80;       /* clear TOF */
        PTD->PTOR = 0x02;       /* toggle blue LED */
    }
}