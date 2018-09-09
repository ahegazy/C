# AVR 7 SEGMENT count up/down and reset
Using Atmega32A microcontroller, with 7 SEGMENT and 3 buttons to count up/down and reset.

## Connection 
- Buttons are connected to pins 0,1 and 2 in PORT D.
- 7 SEGMENT's 'A,B,C,D' are connected to pins 7,6,5,4 and the Enable pin is connection to pin number 2 in PORT C. 
- pin 0 used to count up, pin 1 for count down and pin 2 for reset.


### Used ATmel studio IDE and it automatically includs the io definitions using `avr/io.h`.