/* p7_2.c: A to D conversion of internal temperature

 * This program converts the analog input from channel 26 
 * (internal temperature sensor) using software trigger continuously.
 * Bits 2-0 are used to control the tri-color LEDs. LED code is
 * copied from p2_7.  Put your finger on the target MCU and watch
 * LEDs change color.
 */

#include "MKL25Z4.h"

void ADC0_init(void);
void LED_set(int s);
void LED_init(void);

int main (void)
{
    short int result;
    
    LED_init();                     /* Configure LEDs */
    ADC0_init();                    /* Configure ADC0 */
    
    while (1) {
        ADC0->SC1[0] = 26;          /* start conversion on channel 26 temperature */
        while(!(ADC0->SC1[0] & 0x80)) { } /* wait for COCO */
        result = ADC0->R[0];        /* read conversion result and clear COCO flag */
        LED_set(result);            /* display result on LED */
    }
}

void ADC0_init(void)
{
    SIM->SCGC6 |= 0x8000000;    /* clock to ADC0 */
    ADC0->SC2 &= ~0x40;         /* software trigger */
    /* clock div by 4, long sample time, single ended 12 bit, bus clock */
    ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00;
}

void LED_init(void) {
    SIM->SCGC5 |= 0x400;        /* enable clock to Port B */
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTB->PCR[18] = 0x100;     /* make PTB18 pin as GPIO */
    PTB->PDDR |= 0x40000;       /* make PTB18 as output pin */
    PORTB->PCR[19] = 0x100;     /* make PTB19 pin as GPIO */
    PTB->PDDR |= 0x80000;       /* make PTB19 as output pin */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PTD->PDDR |= 0x02;          /* make PTD1 as output pin */
}

void LED_set(int s) {
    if (s & 1)    /* use bit 0 of s to control red LED */
        PTB->PCOR = 0x40000;    /* turn on red LED */
    else
        PTB->PSOR = 0x40000;    /* turn off red LED */
    
    if (s & 2)    /* use bit 1 of s to control green LED */
        PTB->PCOR = 0x80000;    /* turn on green LED */
    else
        PTB->PSOR = 0x80000;    /* turn off green LED */
    
    if (s & 4)    /* use bit 2 of s to control blue LED */
        PTD->PCOR = 0x02;       /* turn on blue LED */
    else
        PTD->PSOR = 0x02;       /* turn off blue LED */
}