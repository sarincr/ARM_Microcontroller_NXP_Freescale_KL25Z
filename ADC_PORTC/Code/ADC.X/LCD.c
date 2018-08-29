/*
 * File:   LCD.c
 * Author: IBRAHIM LABS
 *
 * Created on June 23, 2013, 7:21 AM
 */

#define CRYSTAL_FREQUENCY 10000000      /*  10 MHz  */
#define FCY CRYSTAL_FREQUENCY/2UL       /*  Cylce frequency 5 MHz*/

#include <p24F16KA102.h>
#include <libpic30.h>
#include <stddef.h>
#include "LCD.h"

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void Initilize_LCD(void)
{
    /*  making Pins as output   */

    ENABLE_DIRECTION    = 0;
    RS_DIRECTION        = 0;
    LCD_BUS_DIRECTION   = 0;

    /*  Writing zero to pins and port   */

    ENABLE_LCD  = 0;
    RS_LCD      = 0;
    LCD_BUS     = 0;
  
   __delay_ms(10);          /*  ten miliseconds delay   */

   /*   writing commonds for initialization of LCD  */

   WriteCmd_LCD(0x38);  /*  Functions Set as Given in Datasheet */
   WriteCmd_LCD(0x0C);  /*  Display ON; Cursor OFF; Blink OFF   */
   WriteCmd_LCD(0x06);  /*  Display Shifting OFF                */
   WriteCmd_LCD(0x01);  /*  Clear Display                       */
  
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void ClearScreen_LCD(void)
{
    WriteCmd_LCD(0x01);         /*  Clear Screen command    */
    __delay_ms(3);              /*  Delay for cursor to return home must be
                                 *  atleast 3ms menstioned in datasheet
                                 */
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void Toggle_Enable_Pin_LCD(void)
{
    /*  toggling Enable PIN is must for data to be displayed on screen
        After every Command and data for more details see datasheet
    */
    ENABLE_LCD = 1;
    __delay_us(200);
    ENABLE_LCD = 0;
    __delay_us(200);
    
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void WriteCmd_LCD(unsigned char Cmd)
{
    RS_LCD  = 0;        /*  For command RS must be low (0)      */
    LCD_BUS &= 0xFF00;  /*  Masking from 16bit register         */
    LCD_BUS |= Cmd;     /*  write Command to data bus of LCD    */

    Toggle_Enable_Pin_LCD();
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void WriteData_LCD(unsigned char Data)
{
    RS_LCD  = 1;        /*  For data RS must be high (1)    */
    LCD_BUS &= 0xFF00;  /*  Masking from 16bit register     */
    LCD_BUS |= Data;    /*  write data to data bus of LCD   */
    
    Toggle_Enable_Pin_LCD();
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void WriteString_LCD(const char *String)
{
    while(*String != NULL)
    {
        WriteData_LCD(*String++);   /*  Display data untill string ends */
    }
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

unsigned char MoveCursorToPosition(unsigned char Address)
{
    /*  valid addresses are for line one 0x80 - 0x8F and line two are 0xC0 - 0xCF   */
    if ((Address >= 0x80 && Address <= 0x8F) || (Address >= 0xC0 && Address <= 0xCF))
    {
        WriteCmd_LCD(Address);
        return 1;
    }
    else
        return 0;
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void WriteIntegerToLCD(unsigned int Integer16Bit)
{

    unsigned char Character[] = "0123456789";

    if (Integer16Bit < 10)
        WriteData_LCD(Character[Integer16Bit]);
    else if (Integer16Bit > 9 && Integer16Bit < 100)
    {
       WriteData_LCD(Character[Integer16Bit/10]);
       WriteData_LCD(Character[Integer16Bit%10]); 
    }
    else if (Integer16Bit > 99 && Integer16Bit < 1000)
    {
       WriteData_LCD(Character[Integer16Bit/100]);
       WriteData_LCD(Character[Integer16Bit%100/10]);
       WriteData_LCD(Character[Integer16Bit%100%10]);
    }
    else if (Integer16Bit > 999 && Integer16Bit < 10000)
    {
        WriteData_LCD(Character[Integer16Bit/1000]);
        WriteData_LCD(Character[Integer16Bit%1000/100]);
        WriteData_LCD(Character[Integer16Bit%1000%100/10]);
        WriteData_LCD(Character[Integer16Bit%1000%100%10]);
    }
    else if (Integer16Bit > 9999)
    {
        WriteData_LCD(Character[Integer16Bit/10000]);
        WriteData_LCD(Character[Integer16Bit%10000/1000]);
        WriteData_LCD(Character[Integer16Bit%10000%1000/100]);
        WriteData_LCD(Character[Integer16Bit%10000%1000%100/10]);
        WriteData_LCD(Character[Integer16Bit%10000%1000%100%10]);
    }
}
