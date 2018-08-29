/* p5_8.c using TPM0 Output Compare

 * This program uses TPM0 CH1 OC to generate periodic output.
 * MCGFLLCLK (41.94 MHz) is used as timer counter clock.
 * Prescaler is set to divided by 128.
 * Timer0 Channel 1 is configured as Output Compare Toggle mode
 * and the output is on PTD1 (blue LED). Every time there is a 
 * match between TPM0_CNT and TPM0_C1V, the output is toggled and 
 * the value in TPM0_C1V is incremented by 2097 that schedules
 * the next match to be in (1 / 41.94 MHz) * 128 * 32766 = 100 ms.
 * The output will toggle every 100 ms or 5 Hz.
 */

#include <MKL25Z4.H>

int main (void) {
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTD->PCR[1] = 0x400;      /* set PTD1 pin for TPM0CH1 */
    
    SIM->SCGC6 |= 0x01000000;   /* enable clock to TPM0 */
    SIM->SOPT2 |= 0x01000000;   /* use MCGFLLCLK as timer counter clock */
    
    TPM0->SC = 0;               /* disable timer while configuring */
    TPM0->SC = 0x07;            /* prescaler /128 */
    TPM0->MOD = 0xFFFF;         /* max modulo value */
    TPM0->CONTROLS[1].CnSC = 0x14;  /* OC toggle mode */
    TPM0->CONTROLS[1].CnSC |= 0x80; /* clear CHF */
    TPM0->CONTROLS[1].CnV = TPM0->CNT + 32766;   /* schedule next transition */
    TPM0->SC |= 0x08;           /* enable timer */

    while (1) {
        while(!(TPM0->CONTROLS[1].CnSC & 0x80)) { } /* wait until the CHF is set */
        TPM0->CONTROLS[1].CnSC |= 0x80;             /* clear CHF */
        TPM0->CONTROLS[1].CnV += 32766;             /* schedule next transition */
    }
}