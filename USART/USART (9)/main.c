
/* p4_4.c UART2 echo

 * This program receives a character from UART2 receiver
 * then sends it back through UART2.
 * The bus clock is set to 13.98 MHz in SystemInit(). 
 * Baud rate = bus clock / BDH:BDL / 16 = 9600
 * A terminal emulator (TeraTerm) should be launched
 * on the host PC. Typing on the PC keyboard sends
 * characters to the FRDM board. The FRDM board echoes
 * the character back to the terminal emulator.
 * The UART2 transmit line is connected to PTD5.
 * The UART2 receive line is connected to PTD4.
 */

#include <MKL25Z4.H>

void UART2_init(void);
void delayMs(int n);

int main (void) {
    char c;
    UART2_init();
    
    while (1) {
        while(!(UART2->S1 & 0x20)) {
        }   /* wait for receive buffer full */
        c = UART2->D ; /* read the char received */

        while(!(UART2->S1 & 0x80)) {
        }   /* wait for transmit buffer empty */
        UART2->D = c; /* send the char received */
    }
}

/* initialize UART2 to transmit and receive at 9600 Baud */
void UART2_init(void) {
    SIM->SCGC4 |= 0x1000;   /* enable clock to UART2 */
    UART2->C2 = 0;          /* disable UART during configuration */
    UART2->BDH = 0x00;
    UART2->BDL = 0x5B;      /* 9600 Baud */
    UART2->C1 = 0x00;       /* normal 8-bit, no parity */
    UART2->C3 = 0x00;       /* no fault interrupt */
    UART2->C2 = 0x0C;       /* enable transmit and receive */
    
    SIM->SCGC5 |= 0x1000;   /* enable clock to PORTD */
    PORTD->PCR[5] = 0x300;  /* PTD5 for UART2 transmit */
    PORTD->PCR[4] = 0x300;  /* PTD5 for UART2 receive */
}