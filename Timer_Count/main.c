/* p5_10.c Counting pulses from PTC12.
 * This is used as the base for P5_10.
 * This program uses TPM0 to count the number of pulses
 * from PTC12.
 * The tri-color LEDs are used to display bit2-0 of
 * the counter. At low frequency input, the change of 
 * LED color should be visible.
 * Although the counter is counting pulses from PTC12,
 * timer counter clock must be present.
 */

#include <MKL25Z4.H>
#include <stdio.h>

int main (void) {

    unsigned short count;

    /* Initialize GPIO pins for tri-color LEDs */
    SIM->SCGC5 |= 0x400;        /* enable clock to Port B */
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTB->PCR[18] = 0x100;     /* make PTB18 pin as GPIO */
    PTB->PDDR |= 0x40000;       /* make PTB18 as output pin */
    PORTB->PCR[19] = 0x100;     /* make PTB19 pin as GPIO */
    PTB->PDDR |= 0x80000;       /* make PTB19 as output pin */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PTD->PDDR |= 0x02;          /* make PTD1 as output pin */
    /* end GPIO pin initialization for LEDs */
    
    /* Start of Timer code */
    SIM->SCGC5 |= 0x0800;       /* enable clock to Port C */
    PORTC->PCR[12] = 0x400;     /* set PTC12 pin for TPM0 */
    
    SIM->SOPT4 &= ~0x01000000;  /* use TPM_CLKIN0 as timer counter clock */
    SIM->SCGC6 |= 0x01000000;   /* enable clock to TPM0 */
    SIM->SOPT2 |= 0x01000000;   /* counter clock must be present */
    TPM0->SC = 0;               /* disable timer while configuring */
    TPM0->SC = 0x80;            /* prescaler /1 and clear TOF */
    TPM0->MOD = 0xFFFF;         /* max modulo value */
    TPM0->CNT = 0;              /* clear counter */
    TPM0->SC |= 0x10;           /* enable timer and use LPTPM_EXTCLK */
    
    while (1) {
        count = TPM0->CNT;
        
        /* change LEDs according to bit 2-0 of the value of count */
        if (count & 1)    /* use bit 0 of count to control red LED */
            PTB->PCOR = 0x40000;    /* turn on red LED */
        else
            PTB->PSOR = 0x40000;    /* turn off red LED */
        
        if (count & 2)    /* use bit 1 of count to control green LED */
            PTB->PCOR = 0x80000;    /* turn on green LED */
        else
            PTB->PSOR = 0x80000;    /* turn off green LED */
        
        if (count & 4)    /* use bit 2 of count to control blue LED */
            PTD->PCOR = 0x02;       /* turn on blue LED */
        else
            PTD->PSOR = 0x02;       /* turn off blue LED */
        /* end of LED code */
    }
}