/*
 * lcd.c
 *
 *  Created on: Feb 18, 2019
 *      Author: AHMAD HEGAZY <https://ahegazy.github.io>
 */


/*
 * LCD 4 Bit Mode connected to TIVAC TM4C123
 * The control pins are connected to PORTA
 * The data pins are connected to PORTC
 * Control pins PORT:PIN  RS=> A:2, RW=> A:3, EN=> A:4
 * Data pins: PORT:PIN Data:4->Data:7 => C:4->C:7
 * */

#include "lcd.h"
/* pins Connections | Control pins PORT A*/
#define RS 2
#define RW 3
#define EN 4

void init_LCD_GPIO(void){
    /* Enable PORT A bit0 & C bit 2 clocks for LCD 0000 0101 */
    SYSCTL_RCGCGPIO_R |= 0x05; // 0101
    /* SET ports A, bits 2,3,4, as output 1, 0001 1100 */
    GPIO_PORTA_DIR_R |= 0x1c;
    /* SET ports F, bits 4,5,6,7, as output 1, 1111 0000 */
    GPIO_PORTC_DIR_R |= 0xF0;
    /* Alternate function 0 */
    GPIO_PORTA_AFSEL_R &= ~0x1c;
    GPIO_PORTC_AFSEL_R &= ~0xf0;
    /* 2mA output current as per LCD characteristics  */
    GPIO_PORTA_DR2R_R |=  0x1c;
    GPIO_PORTC_DR2R_R |= 0xf0;
    /* Enable Digital*/
    GPIO_PORTA_DEN_R |=  0x1c;
    GPIO_PORTC_DEN_R |= 0xf0;

}

void LCD_setPORTData(uint8_t d){
    /* Data4->D7, PORTC4-> C7 */
    uint8_t i;
    d &= 0x0f; /* don't need the MSnibble.*/
    /*
     bit -> pin in PORT C
     0 -> 4
     1 -> 5
     2 -> 6
     3 -> 7
     */
    for(i=0;i<4;i=i+1){
        GPIO_PORTC_BIT_DATA(i+4) = (d & (1<<i)) ? 0xff : 0x00;
    }
}

void LCD_cmd(uint8_t cmd){
    /* Enable LCD bin 4; command mode bin 2; write bin 3 '0x00 to write',*/
    GPIO_PORTA_BIT_DATA(RW) = 0x00; /* WRITE on LCD bin 3 -> 0x00 */
    GPIO_PORTA_BIT_DATA(RS) = 0x00; /* Command mode LCD bin 2 -> 0x00 */
    LCD_setPORTData(cmd);
    GPIO_PORTA_BIT_DATA(EN) = 0xff;/* Enable LCD bin 4 -> 0xff */
    delay_ms(1);
    GPIO_PORTA_BIT_DATA(EN) = 0x00;/* Disable LCD bin 4 -> 0 */
    delay_ms(1);
}

void LCD_clear(void)
{
    LCD_cmd(0);
    LCD_cmd(1);
}

void init_LCD(void){
    init_LCD_GPIO();
    LCD_setPORTData(0x00);
    delay_ms(20);
    ///////////// Reset process from datasheet /////////
    LCD_cmd(0x03);
    delay_ms(5);
    LCD_cmd(0x03);
    delay_ms(11);
    LCD_cmd(0x03);
    /////////////////////////////////////////////////////
    LCD_cmd(0x02);
    LCD_cmd(0x02);
    LCD_cmd(0x08);
    LCD_cmd(0x00);
    LCD_cmd(0x0C);
    LCD_cmd(0x00);
    LCD_cmd(0x06);
    LCD_clear();

}


void LCD_WriteChar(char c)
{
    char temp,y;
    temp = c&0x0F;
    y = c&0xF0;
    GPIO_PORTA_BIT_DATA(RS) = 0xff; /* data mode LCD bin 2 -> 0xff */
    LCD_setPORTData(y>>4);             //Data transfer MSByte
    GPIO_PORTA_BIT_DATA(EN) = 0xff;
    delay_ms(1);
    GPIO_PORTA_BIT_DATA(EN) = 0x00;
    delay_ms(1);

    LCD_setPORTData(temp); /* Send LSByte*/
    GPIO_PORTA_BIT_DATA(EN) = 0xff;
    delay_ms(1);
    GPIO_PORTA_BIT_DATA(EN) = 0x00;
    delay_ms(1);
}


void LCD_WriteString(char *s)
{
    int i;
    for(i=0;s[i]!='\0';i++){
        LCD_WriteChar(s[i]);
        if (i == 15){ /* new line */
            LCD_SetCursor(2,0);
        }
    }
}


void LCD_ShiftRight(void)
{
    LCD_cmd(0x01);
    LCD_cmd(0x0C);
}

void Lcd_ShiftLeft(void)
{
    LCD_cmd(0x01);
    LCD_cmd(0x08);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    char temp,z,y;
    if(row == 1) /* row 1 */
    {
        temp = 0x80 + col;
        z = temp>>4;
        y = (0x80+col) & 0x0F;
        LCD_cmd(z);
        LCD_cmd(y);
    }else if(row == 2) /* row 2 */
    {
        temp = 0xC0 + col;
        z = temp>>4;
        y = (0xC0+col) & 0x0F;
        LCD_cmd(z);
        LCD_cmd(y);
    }
}

