#include "MKL25Z4.h"                    // Device header


int main (void) {
    PORTD->PCR[0] = 0x100;      /* make PTD0 pin as GPIO */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PORTD->PCR[7] = 0x103;      /* make PTD7 pin as GPIO and enable pullup */
    PTD->PDDR |= 0x03;          /* make PTD0-1 as output pin */
    PTD->PDDR &= ~0x80;         /* make PTD7 as input pin */
    
    if((PTD->PDIR & 0x80) == 0)
    {   /* PTD7 == 0 */
        PTD->PDOR &= ~0x02;     /* Relay 2 = Off */
        PTD->PDOR |= 0x01;      /* Relay 1 = On */
    }
    else
    {   /* PTD7 == 1 */
        PTD->PDOR &= ~0x01;     /* Relay 1 = 0ff */
        PTD->PDOR |= 0x02;      /* Relay 2 = 0n */
    }
}