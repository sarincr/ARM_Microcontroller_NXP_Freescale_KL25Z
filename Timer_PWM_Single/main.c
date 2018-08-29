/*
 * This program drives a standard servo motor.
 *
 * The TPM1_CH0 is used in PWM mode to generate a 50 Hz signal
 * with pulse width between 1 ms and 2 ms.
 * The quad half-H-bridge motor driver (TB6612FNG) 
 * is configured so that the output of the PWM is also available at M1 terminal.
 *
 */

#include "MKL25Z4.h"

void delayMs(int n);

int main(void)
{
    int pw = 0;

    /* enable PTC 3 as output */
    SIM->SCGC5 |= 0x800;        /* enable clock to Port C */
    PORTC->PCR[3] = 0x100;      /* make PTC3 pin as GPIO */
    PTC->PDDR |= 0x08;          /* make PTC3 as output pin */
    PTC->PSOR = 1 << 3;
    
    /* enable PTA 12 as output of TPM1_CH0 */
    SIM->SCGC5 |= 0x200;        /* enable clock to Port A */
    PORTA->PCR[12] = 0x300;     /* make PTA12 pin as TPM1 output */

    /* enable TPM1_CH0 */
    SIM->SCGC6 |= 0x2000000u;   /* enable clock to TPM1 */
    SIM->SOPT2 |= 0x01000000;   /* use MCGFLLCLK as timer counter clock */
    TPM1->SC = 0;               /* disable timer */
    TPM1->CONTROLS[0].CnSC = 0x20 | 0x08;   /* edge-aligned, pulse high */
    TPM1->MOD = 41900;           /* Set up modulo register for 50Hz */
    TPM1->CONTROLS[0].CnV = 100;  /* Startup dutycycle */
    TPM1->SC = 0x0C;            /* enable TPM1 with prescaler /16 */

    while(1)
    {
        for (pw = 2620 - 1; pw < 5240 - 1; pw += 100)
        {
            TPM1->CONTROLS[0].CnV = pw;
            delayMs(100);
        }
    }
}

/* delay n milliseconds (41.94 MHz CPU clock) */
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 7000; j++)
            {}  /* do nothing */
}