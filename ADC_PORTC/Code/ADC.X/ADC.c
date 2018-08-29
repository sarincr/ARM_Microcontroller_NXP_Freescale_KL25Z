#define CRYSTAL_FRQUENCY   10000000             /*  10MHz crystal   */
#define FCY CRYSTAL_FRQUENCY/2UL                /*  Cycle frequency */

#include <p24F16KA102.h>
#include <libpic30.h>
#include "ADC.h"

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void ConfigModuleADC(void)
{
    AD1CON1bits.ADON = 0;
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.SAMC = 0b1111;
    AD1CON3bits.ADCS = 0b0000000;

    AD1CON2bits.CSCNA = 0;
    AD1CON2bits.BUFS = 0;
    AD1CON2bits.SMPI = 0b00000;
    AD1CON2bits.BUFM = 0;
    AD1CON2bits.ALTS = 0;

    AD1CON1bits.ADSIDL = 0;
    AD1CON1bits.FORM = 0b00;
    AD1CON1bits.SSRC = 0b0000;
    AD1CON1bits.ASAM = 0;

}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void ChangeChannelADC(unsigned char CHANNEL)
{
    AD1CON1bits.ADON = 0;                       /*  ADC OFF         */
    __delay_us(100);
    AD1CHSbits.CH0SA = (CHANNEL & 0b00011111);  /*  Channel Changed */
    __delay_us(100);
    AD1CON1bits.ADON = 1;                       /*  ADC ON          */
    
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

unsigned int SamplingAndConversionADC(void)
{
    AD1CON1bits.SAMP = 1;                       /*  Start sampling input    */
    while(!AD1CON1bits.SAMP);
    AD1CON1bits.SAMP = 0;                       /*  End sampling */
    while(AD1CON1bits.SAMP);
    while(!AD1CON1bits.DONE);
    return ADC1BUF0;
}
