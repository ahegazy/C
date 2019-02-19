# ARM TivaC-tm4c123 LCD Driver and Time Delays
Using ARM TivaC-tm4c123 microcontroller local Timer for delays,and GPIO pins to drive an LCD in 4-bit mode.

## Specs
1. Microseconds and Milliseconds delays.
2. LCD write character and string. 
3. LCD Move and shift Curser to a certain location row/col.

## Usage 
- See the example in ```main.c```
1. Include the ```hw_gpio.h```, ```delay.h``` and ```lcd.h``` header files.
2. Initialize the LCD by calling ```void init_LCD(void)``` function.
3. use the ```void LCD_WriteChar(char c)``` function to write character.
4. if you want to write a string; store send a pointer to 1st char the call ```LCD_WriteString(char *s)``` function.
5. call ```void LCD_clear(void)``` function to clear the LCD.
6. you can set delays between writing using ```delay_ms(time)``` macro.

## This code was written and tested on TivaC-tm4c123 using CodeComposerStudio IDE.
