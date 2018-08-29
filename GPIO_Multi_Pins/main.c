
#include "MKL25Z4.h"

void delayMs(int n);
int i=0;

int main(void)
{
    /* enable PTC 6-3 as output for LEDs */
   SIM->SCGC5 |= 0x800;        /* enable clock to Port C */
	//SIM->SCGC5= 0b1000,0000,0000
	 //SIM->SCGC5|= SIM_SCGC5_PORTD_MASK; 
	for(i=3;i<7;i++)
	{
    PORTC->PCR[i] = 0x100;      /* make PTCi pin as GPIO */
		//PORTC->PCR[i] = 1UL << 4;
	   //PORTC->PCR[i] =	PORT_PCR_MUX(1UL);
	}
    // make PTC6-3 as output pin
		//PTC->PDDR |= (1UL << 3|1UL << 4|1UL << 5|1UL << 6);
		//PTC->PDDR |= 0b01111000;
	  PTC->PDDR |= 0x78;
		
		for (;;)
    {
        PTC->PCOR = 0x50;       /* turn off PTC6, PTC4 0b1010000*/
			  //PTC->PCOR = 0b1010000; 
			  PTC->PSOR = 0x28;       /* turn on PTC5, PTC3 0b101000 */
        delayMs(500);
        PTC->PCOR = 0x28;       /* turn off PTC5, PTC3 */
        PTC->PSOR = 0x50;       /* turn on PTC6, PTC4 */
        delayMs(500);
    }
}

// delay n milliseconds (41.94MHz CPU clock)
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 7000; j++)
            {}  /* do nothing */
}