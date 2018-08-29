#include "MKL25Z4.h"                    // Device header


int led_on(int led);
int led_off(int led);

int get_key(void);

int main(void)
{
  SIM->SCGC5 = SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTA_MASK;
  
  PORTB->PCR[6] = PORT_PCR_MUX(1);
  PORTB->PCR[7] = PORT_PCR_MUX(1);
  PORTB->PCR[10] = PORT_PCR_MUX(1);

  PTB->PDDR = (1 << 6) | (1 << 7) | (1 << 10);

  led_off(6);
	led_on(6)
	led_off(7);
  led_off(10);
}

int led_on(int led)
{
  PTB->PCOR = (1<<led);
	return 0;
}

int led_off(int led)
{
  PTB->PSOR = (1<<led);
	return 0;
}

int get_key()
{
	return 0;
}