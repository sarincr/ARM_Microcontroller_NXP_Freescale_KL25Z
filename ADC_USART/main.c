/* p7_3.c: A to D conversion of channel 0

 * This program converts the analog input from channel 0 (PTE20) 
 * using software trigger continuously. PTE20 is connected to
 * an LM34 Fahrenheit temperature sensor. The conversion result
 * is displayed as temperature through UART0 virtual serial port.
 * 16-bit precision is used for conversion. At higher precision,
 * the noise is more significant so 32 samples averaging is used.
 * The LM34 output voltage is 10mV/degreeF. The ADC of FRDM-KL25Z
 * uses 3.3V as Vref so:
 * temperature = result * 330.0 / 65536
 * Open a terminal emulator at 115200 Baud rate at the host PC and
 * observe the output.
 */

#include "MKL25Z4.h"
#include <stdio.h>

void ADC0_init(void);
void delayMs(int n);
void UART0_init(void);
void UART0Tx(char c); 
void UART0_puts(char* s);

int main (void) {
    int result;
    float temperature;
    char buffer[16];

    ADC0_init();                    /* Configure ADC0 */
    UART0_init();                   /* initialize UART0 for output */
    
    while (1) {
        ADC0->SC1[0] = 0;           /* start conversion on channel 0 */
        while(!(ADC0->SC1[0] & 0x80)) { } /* wait for COCO */
        result = ADC0->R[0];        /* read conversion result and clear COCO flag */
        temperature = result * 100 / 65536;  /* convert voltage to temperature */
        sprintf(buffer, "\r\nTemp = %6.2fF", temperature); /* convert to string */
        UART0_puts(buffer);         /* send the string through UART0 for display */
        delayMs(1000);
    }
}

void ADC0_init(void)
{
    SIM->SCGC5 |= 0x2000;       /* clock to PORTE */
    PORTE->PCR[20] = 0;         /* PTE20 analog input */

    SIM->SCGC6 |= 0x8000000;    /* clock to ADC0 */
    ADC0->SC2 &= ~0x40;         /* software trigger */
    ADC0->SC3 |= 0x07;          /* 32 samples average */
    /* clock div by 4, long sample time, single ended 16 bit, bus clock */
    ADC0->CFG1 = 0x40 | 0x10 | 0x0C | 0x00;
}

/* initialize UART0 to transmit at 115200 Baud */
void UART0_init(void) {
    SIM->SCGC4 = 0x0400;    /* enable clock for UART0 */
    SIM->SOPT2 = 0x04000000;    /* use FLL output for UART Baud rate generator */
    UART0->C2 = 0;          /* turn off UART0 while changing configurations */
    UART0->BDH = 0x00;
    UART0->BDL = 0x17;      /* 115200 Baud */
    UART0->C4 = 0x0F;       /* Over Sampling Ratio 16 */
    UART0->C1 = 0x00;       /* 8-bit data */
    UART0->C2 = 0x08;       /* enable transmit */

    SIM->SCGC5 = 0x0200;    /* enable clock for PORTA */
    PORTA->PCR[2] = 0x0200; /* make PTA2 UART0_Tx pin */
}


void UART0Tx(char c) {
    while(!(UART0->S1 & 0x80)) {
    }   /* wait for transmit buffer empty */
    UART0->D = c; /* send a char */
}

void UART0_puts(char* s) {
    while (*s != 0)         /* if not end of string */
        UART0Tx(*s++);      /* send the character through UART0 */
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