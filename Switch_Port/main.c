#include "MKL25Z4.h"                    // Device header
int i=0;
int main (void) 
{
		SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
    void delayMs(int n);
	for(i=0;i<4;i++)
	{
    PORTD->PCR[0] = 0x100;      // make PTD0 -PDT3 pin as GPIO 
	}
    PTD->PDDR |= 0x0F;          // make PTD0-PTD3 as output pin 0b0000 1111
	  PTD->PDDR &= ~0x80;         // make PTD7 as input pin * ~(0b10000000)
    
    if((PTD->PDIR & 0x80) == 0)
    {   /* PTD7 == 0 */
        PTD->PDOR &= ~0x0F;     /* open all switches */
        delayMs(100);           /* wait 0.1 second */
        PTD->PDOR |= 0x09;      /* close SW1 & SW4 */

        while((PTD->PDIR & 0x80) == 0) ;    /*PTD7 == 0 */
    }
    else
    {   /* PTD7 == 1 */
        PTD->PDOR &= ~0x0F;     /* open all switches */
        delayMs(100);           /* wait 0.1 second */
        PTD->PDOR |= 0x06;      /* close SW2 & SW3 */
        while((PTD->PDIR & 0x80) != 0) ;    /*PTD7 == 0 */
    }
}