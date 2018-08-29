/* p4_1.c UART0 transmit

 * Sending "YES" to UART0 on Freescale FRDM-KL25Z board.
 * UART0 is connected to openSDA debug agent and has
 * a virtual connection to the host PC COM port.
 * Use TeraTerm to see the message "YES" on a PC.

 * By default in SystemInit(), FLL clock output is 41.94 MHz.
 * Setting BDH=0, BDL=0x17, and OSR=0x0F yields 115200 Baud.
 */

#include <MKL25Z4.H>

void UART0_init(void);
void delayMs(int n);

int main (void) {
    UART0_init();
    
    while (1) {
        while(!(UART0->S1 & 0x80)) {
        }   /* wait for transmit buffer empty */
        UART0->D = 'Y'; /* send a char */
        while(!(UART0->S1 & 0x80)) { }
        UART0->D = 'e'; /* send a char */
        while(!(UART0->S1 & 0x80)) { }
        UART0->D = 's'; /* send a char */
        delayMs(2); /* leave a gap between messages */
    }
}

/* initialize UART0 to transmit at 115200 Baud */
void UART0_init(void) {
    SIM->SCGC4 |= 0x0400;   /* enable clock for UART0 */
    SIM->SOPT2 |= 0x04000000;    /* use FLL output for UART Baud rate generator */
    UART0->C2 = 0;          /* turn off UART0 while changing configurations */
    UART0->BDH = 0x00;
    UART0->BDL = 0x17;      /* 115200 Baud */
    UART0->C4 = 0x0F;       /* Over Sampling Ratio 16 */
    UART0->C1 = 0x00;       /* 8-bit data */
    UART0->C2 = 0x08;       /* enable transmit */

    SIM->SCGC5 |= 0x0200;   /* enable clock for PORTA */
    PORTA->PCR[2] = 0x0200; /* make PTA2 UART0_Tx pin */
}

/* Delay n milliseconds */
/* The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit(). */

void delayMs(int n) {
    int i;
    int j;
    for(i = 0 ; i < n; i++)
        for (j = 0; j < 7000; j++) {}
}