/* p10_2.c: Stepper motor control
/* This program controls a unipolar stepper motor using PTD 3, 2, 1, 0. */

#include <MKL25Z4.H>

int delay = 100;
int direction = 0;

int main (void) {
    void delayMs(int n);
    
    const char steps[ ] = {0x9, 0x3, 0x6, 0xC}; //1001,0101,0110,1100
    int i = 0;    
    
    /* PTD 3, 2, 1, 0 for motor control */
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTD->PCR[0] = 0x100;      /* make PTD0 pin as GPIO */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PORTD->PCR[2] = 0x100;      /* make PTD2 pin as GPIO */
    PORTD->PCR[3] = 0x100;      /* make PTD3 pin as GPIO */
    PTD->PDDR |= 0x0F;          /* make PTD3-0 as output pin */

    for (;;) {
        if (direction)
            PTD->PDOR = (steps[i++ & 3]);
        else
            PTD->PDOR = (steps[i-- & 3]);
        delayMs(delay);
    }
}

/* Delay n milliseconds */
/* The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit(). */

void delayMs(int n) {
    int i;
    int j;
    for(i = 0 ; i < n; i++)
        for (j = 0; j < 7000; j++) {}
}