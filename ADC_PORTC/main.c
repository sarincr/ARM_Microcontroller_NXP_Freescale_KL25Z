/*
 * This program sets up ADC0 convert channel 9 and writes the 
 * conversion result to the LEDs.
 * Analog channel 9 uses PTB1 pin and is connected to
 * a potentiometer on Wytec EduBase board.
 */

#include "MKL25Z4.h"

void ADC0_init(void);
void delayMs(int n);

int main (void)
{
    short int result;
    
    /* enable PTC 6-3 as output for LEDs */
    SIM->SCGC5 |= 0x800;        /* enable clock to Port C */
    PORTC->PCR[3] = 0x100;      /* make PTC3 pin as GPIO */
    PORTC->PCR[4] = 0x100;      /* make PTC4 pin as GPIO */
    PORTC->PCR[5] = 0x100;      /* make PTC5 pin as GPIO */
    PORTC->PCR[6] = 0x100;      /* make PTC6 pin as GPIO */
    PTC->PDDR |= 0x78;          /* make PTC6-3 as output pin */

    ADC0_init();                    /* Configure ADC0 */
    
    while (1) {
        ADC0->SC1[0] = 9;           /* start conversion on channel 9 */
        while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
        result = ADC0->R[0];        /* read conversion result and clear COCO flag */
        PTC->PDOR = result >> 5;       /* display result on LED */
    }
}

void ADC0_init(void)
{
    SIM->SCGC5 |= 0x0400;       /* clock to PORTB */
    PORTB->PCR[1] = 0;          /* PTB1 analog input */

    SIM->SCGC6 |= 0x8000000;    /* clock to ADC0 */
    ADC0->SC2 &= ~0x40;         /* software trigger */
    /* clock div by 4, long sample time, single ended 12 bit, bus clock */
    ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00;
}

// delay n milliseconds (41.94MHz CPU clock)
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 7000; j++)
            {}  /* do nothing */
}