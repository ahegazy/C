/*
 * lcd.h
 *
 *  Created on: Feb 18, 2019
 *      Author: AHMAD
 */

#ifndef LCD_H_
#define LCD_H_

#include "hw_gpio.h"
#include <stdint.h>
#include "delay.h"

void init_LCD_GPIO(void);
void LCD_setPORTData(uint8_t d);
void LCD_cmd(uint8_t cmd);
void LCD_clear(void);
void init_LCD(void);
void LCD_WriteChar(char c);
void LCD_WriteString(char *s);
void LCD_ShiftRight(void);
void Lcd_ShiftLeft(void);
void LCD_SetCursor(uint8_t row, uint8_t col);



#endif /* LCD_H_ */
