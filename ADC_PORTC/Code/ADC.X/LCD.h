/* 
 * File:   LCD.h
 * Author: IBRAHIM LABS
 *
 * Created on June 23, 2013, 7:18 AM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

    /*  *****************************************************************   */

    #define LCD_BUS     LATB                        /*  DATA BUS FOR LCD 8bits  */
    #define ENABLE_LCD  LATBbits.LATB9              /*  Enable pin of LCD       */
    #define RS_LCD      LATBbits.LATB8              /*  RS pin of LCD           */

    #define LCD_BUS_DIRECTION   TRISB               /*  DATA bus tristate register  */
    #define ENABLE_DIRECTION    TRISBbits.TRISB9    /*  Enable pin tristate register*/
    #define RS_DIRECTION        TRISBbits.TRISB8    /*  RS pin tristate register    */

/*--------------------------------------------------------------------------------------------*/

    /*  Functions for LCD   */

    void Initilize_LCD(void);
    void ClearScreen_LCD(void);
    void Toggle_Enable_Pin_LCD(void);
    void WriteCmd_LCD(unsigned char Cmd);
    void WriteData_LCD(unsigned char Data);
    void WriteString_LCD(const char *String);
    unsigned char MoveCursorToPosition(unsigned char Address);
    void WriteIntegerToLCD(unsigned int Integer16Bit);

/*  *****************************************************************   */

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

