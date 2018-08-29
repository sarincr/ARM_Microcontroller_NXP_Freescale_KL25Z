/* p4_3.c Sending "Hello" through UART2

 * This program sends a message "Hello" through UART2.
 * The bus clock is set to 13.98 MHz in SystemInit(). 
 * Baud rate = bus clock / BDH:BDL / 16 = 9600
 * A terminal emulator (TeraTerm) should be launched
 * on the host PC to display the message.
 * The UART2 transmit line is connected to PTD5.
 */

#include <MKL25Z4.H>

void UART2_init(void);
void delayMs(int n);

int main (void) {
    char message[] = "Hello\r\n";
    int i;

    UART2_init();
    
    while (1) {
        for (i = 0; i < 7; i++) {
            while(!(UART2->S1 & 0x80)) {
            }   /* wait for transmit buffer empty */
            UART2->D = message[i]; /* send a char */
        }
        delayMs(200); /* leave a gap between messages */
    }
}

/* initialize UART2 to transmit at 9600 Baud */
void UART2_init(void) {
    SIM->SCGC4 |= 0x1000;   /* enable clock to UART2 */
    UART2->C2 = 0;          /* disable UART during configuration */
    UART2->BDH = 0x00;
    UART2->BDL = 0x5B;      /* 9600 Baud */
    UART2->C1 = 0x00;       /* normal 8-bit, no parity */
    UART2->C3 = 0x00;       /* no fault interrupt */
    UART2->C2 = 0x08;       /* enable transmit, no interrupt */
    
    SIM->SCGC5 |= 0x1000;   /* enable clock to PORTD */
    PORTD->PCR[5] = 0x300;  /* PTD5 for UART2 transmit */
}

/* Delay n milliseconds */
/* The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit(). */

void delayMs(int n) {
    int i;
    int j;
    for(i = 0 ; i < n; i++)
        for (j = 0; j < 7000; j++) {}
}