/* p5_3.c Toggling green LED using SysTick delay

 * This program uses SysTick to generate one second delay to
 * toggle the green LED.
 * System clock is running at 41.94 MHz. SysTick is configure
 * to count down from 41939 to give a 1 ms delay.
 * For every 1000 delays (1 ms * 1000 = 1 sec), toggle the
 * green LED once.  The green LED is connected to PTB19.
 */

#include <MKL25Z4.H>

int main (void) 
	{
    void delayMs(int n);
    
    SIM->SCGC5 |= 0x400;        /* enable clock to Port B */
    PORTB->PCR[19] = 0x100;     /* make PTB19 pin as GPIO */
    PTB->PDDR |= 0x080000;      /* make PTB19 as output pin */
    
    while (1) 
		{
        delayMs(1000);          /* delay 1000 ms */
        PTB->PTOR = 0x080000;   /* toggle green LED */
    }
}

void delayMs(int n) 
	{
	
    int i;
    SysTick->LOAD = 41940 - 1;
    SysTick->CTRL = 0x5; /* Enable the timer and choose sysclk as the clock source */

    for(i = 0; i < n; i++) 
		{
        while((SysTick->CTRL & 0x10000) == 0) /* wait until the COUTN flag is set */
            { }
    }
    SysTick->CTRL = 0;  /* Stop the timer (Enable = 0) */
}