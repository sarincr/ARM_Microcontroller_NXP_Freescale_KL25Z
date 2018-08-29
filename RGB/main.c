/* p2_7.c Cycle through all color combinations of LEDs on FRDM-KL25Z board.
 * This program displays all eight combinations of the
 * three LEDs on the FRDM-KL25Z board.
 * The red LED is connected to PTB18.
 * The green LED is connected to PTB19.
 * The blue LED is connected to PTD1.
 * The LEDs are low active (a '0' turns ON the LED).
 */

#include <MKL25Z4.H>

int main (void) 
	{
    void delayMs(int n);
   
    
    SIM->SCGC5 |= 0x400;        /* enable clock to Port B */
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTB->PCR[18] = 0x100;     /* make PTB18 pin as GPIO */
    PTB->PDDR |= 0x40000;       /* make PTB18 as output pin */
    PORTB->PCR[19] = 0x100;     /* make PTB19 pin as GPIO */
    PTB->PDDR |= 0x80000;       /* make PTB19 as output pin */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PTD->PDDR |= 0x02;          /* make PTD1 as output pin */
    
    while (1) 
			{
				
        		/* use bit 0 of counter to control red LED */
            PTB->PCOR = 0x40000;				/* turn on red LED */
				    delayMs(2000);
            PTB->PSOR = 0x40000;    /* turn off red LED */
            PTB->PCOR = 0x80000;    /* turn on green LED */
					  delayMs(2000);
            PTB->PSOR = 0x80000;    /* turn off green LED */
            PTD->PCOR = 0x02;       /* turn on blue LED */
					  
						delayMs(2000);
            PTD->PSOR = 0x02;       /* turn off blue LED */
            
  }
}
/* Delay n milliseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */
void delayMs(int n) 
{
    int i;
    int j;
    for(i = 0 ; i < n; i++)
        for (j = 0; j < 7000; j++) {}
}