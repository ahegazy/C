/*
 * main.c
 *
 *  Created on: Feb 16, 2019
 *      Author: AHMAD HEGAZY <https://ahegazy.github.io>
 */

#include "hw_gpio.h"
#include <stdint.h>
#include "delay.h"
#include "lcd.h"

int main(void){
    int i = 0;
    char *data = "LCD DRIVER ...";
    char *l1 = "AHMAD HEGAZY"; /* line 1 */
    char *l2 = "github/ahegazy"; /* line 2 */

    init_LCD(); /* Initialize GPIO pins and LCD.*/
    LCD_WriteString(data);
    delay_ms(500);

    while(1){
        LCD_clear();
        for(i=0;l1[i] != '\0'; i=i+1){
            LCD_WriteChar(l1[i]);
            delay_ms(100);
        }
        
        LCD_SetCursor(2,0);
        delay_ms(500);

        for(i=0;l2[i] != '\0'; i=i+1){
            LCD_WriteChar(l2[i]);
            delay_ms(100);
        }
        delay_ms(2000);

    }
    return 0;
}
