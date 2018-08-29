/* p2_8.c Read a switch and write it to the LED. 

 * This program reads an external SW connected to PTA1 
 * of FRDM board and writes the value to the green LED. 
 * When switch is pressed, it connects PTA1 to ground. 
 * PTA1 pin pull-up is enabled so that it is high when 
 * the switch is not pressed.	
 * LED is on when low. 
 */

#include <MKL25Z4.H>

int main (void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;        /* enable clock to Port B */
    PORTB->PCR[19] = PORT_PCR_MUX(1UL);     /* make PTB19 pin as GPIO */
    PTB->PDDR |= 1UL << 19;       /* make PTB19 as output pin */
    
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;        /* enable clock to Port A */
    PORTA->PCR[1] = PORT_PCR_MUX(1UL);      /* make PTA1 pin as GPIO and enable pull-up */
    PTA->PDDR &= ~(1UL << 1);         /* make PTA1 as input pin */
    
    while (1) 
		{
        if (PTA->PDIR & (1UL << 1))      /* check to see if switch is pressed */
            PTB->PSOR = 0x80000;    /* if not, turn off green LED */
        else
            PTB->PCOR = 0x80000;    /* turn on green LED */
    }
}