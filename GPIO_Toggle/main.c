/* p2_5.c Toggling LED in C using PSOR, PCOR, and PTOR registers. 
 * This program toggles green LED for 0.5 second ON and 0.5 second OFF.
 * The green LED is connected to PTB19.
 * The LEDs are low active (a '0' turns ON the LED).
 */

#include <MKL25Z4.H>

int main (void) {
    void delayMs(int n);
    
    SIM->SCGC5 |= 0x400;        /* enable clock to Port B */
    PORTB->PCR[19] = 0x100;     /* make PTB19 pin as GPIO (See Table 2-4)*/
    PTB->PDDR |= 0x80000;       /* make PTB19 as output pin */
    
    while (1) 
		{
        
        PTB->PTOR = 0x80000;    /* Toggle green LED */
        delayMs(500);
        PTB->PTOR = 0x80000;    /* Toggle green LED */
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