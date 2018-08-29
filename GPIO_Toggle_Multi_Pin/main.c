/* p2_6.c Toggling all three LEDs on FRDM-KL25Z board. 
 * This program toggles all three LEDs on the FRDM-KL25Z board.
 * The red LED is connected to PTB18.
 * The green LED is connected to PTB19.
 * The blue LED is connected to PTD1.
 * The LEDs are low active (a '0' turns ON the LED).
 */

#include <MKL25Z4.H>

int main (void) {
    void delayMs(int n);
    
    SIM->SCGC5 |= 0x400;        /* enable clock to Port B */
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTB->PCR[18] = 0x100;     /* make PTB18 pin as GPIO (See Table 2-4)*/
    PORTB->PCR[19] = 0x100;     /* make PTB19 pin as GPIO */
    PTB->PDDR |= 0xC0000;       /* make PTB18, 19 as output pin */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PTD->PDDR |= 0x02;          /* make PTD1 as output pin */
    
    while (1) {
        PTB->PDOR &= ~0xC0000;  /* turn on red and green LED */
        PTD->PDOR &= ~0x02;     /* turn on blue LED */
        delayMs(500);
        PTB->PDOR |= 0xC0000;   /* turn off red and green LED */
        PTD->PDOR |= 0x02;      /* turn off blue LED */
        delayMs(500);
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