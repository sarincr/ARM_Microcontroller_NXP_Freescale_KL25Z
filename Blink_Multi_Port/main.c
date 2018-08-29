#include "MKL46Z4.h"
uint32_t i = 0;
const uint32_t LEDPin[] = { 1UL << 1, 1UL << 19 };


void InitLED(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK ;
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	
	
	PORTD->PCR[1] = PORT_PCR_MUX(1UL);
	PTD->PDDR |= LEDPin[0];
	
	
	PORTB->PCR[19] = PORT_PCR_MUX(1UL);
	PTB->PDDR |= LEDPin[1];
}
void BlinkLED(void)
{

	PTD->PSOR = LEDPin[0];
	PTB->PCOR = LEDPin[1];

	for(i = 0; i < 3000000; i++){};

	PTD->PCOR = LEDPin[0];
	PTB->PSOR = LEDPin[1];
		
	for(i = 0; i < 3000000; i++){};
		
	
	
}
int main(void)
	{
	InitLED();
	
	while(1)
	{
	BlinkLED();
	}
}