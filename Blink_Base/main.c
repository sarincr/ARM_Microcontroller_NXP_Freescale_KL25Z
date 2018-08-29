// This Program Shows how to blink the a LED connected to Pin 19 of Port B

// Step :1  - Include the Header files for Built in Functional  Referencing 
#include "MKL25Z4.h"                    // Device header

// Step :2  - Initialise and define the main function
int main(void)
	{
	// Step :3  - Declare port configuration bits for a selected pin
	//Define the system clock configuration for selected Ports
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	//Select the required pins for the port
	
	/*Port control and interrupt module  has 32-pin ports  
	All pins  of All Ports are not available on the device. 
	Some Ports have bee assigned for some special functions. 
	• Port A and Port D is each assigned one interrupt. 
	•	For DMA requests, Port A and Port D each have a dedicated input to the DMA MUX.
  To Set/Reset and read/write the bits of a port is charectersised by fields within the PORTx_PCRn 		*/

	/* Example:Pull Enable
		This bit is read only for pins that do not support a configurable pull resistor. 
		Multiplexing and Signal Descriptions for the pins that support a configurable pull resistor.
		Pull configuration is valid in all digital pin muxing modes.
		0 Internal pullup or pulldown resistor is not enabled on the corresponding pin.
		1 Internal pullup */
	
	//Freedom board has inbuilt LED connected to the pin 19 of Port B 
	
	PORTB->PCR[19] = PORT_PCR_MUX(1UL);
	PTB->PDDR |= 1UL << 19;
// Step : 4 - Create a Infifnte loop  
	while(1) 
	{
// Step : 5 - 	Declare an iterative integer variable 'i' 
	uint32_t i = 0;
	// To Turn led on Pin 19 of Port B, Set 19th bit of Port Set Output Register pf Port B (GPIOx_PSOR) which will creat a BIT_HIGH on that pin
	PTB->PSOR = 1UL << 19;
	// Create a for loop for a delay
	for(i = 0; i < 3000000; i++){};
		// To Turn led off Pin 19 of Port B, Set 19th bit of Port Clear Output Register (GPIOx_PCOR) which will creat a BIT_LOW on that pi
	PTB->PCOR = 1UL << 19;
	// Create a for loop for a delay
	for(i = 0; i < 3000000; i++){};	
	}
}