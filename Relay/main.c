
/* p10_1: Relay control

 * This program turns the relay connected to PTD1 on and off every second.
 */

#include <MKL25Z4.H>

int main (void) {
    void delayMs(int n);
    
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PTD->PDDR |= 0x02;          /* make PTD1 as output pin */
    
    while (1) {
        PTD->PSOR = 0x02;       /* turn on PTD1 output */
        delayMs(1000);          /* wait for 1 second */
        PTD->PCOR = 0x02;       /* turn off PTD1 output */
        delayMs(1000);          /* wait for 1 second */
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