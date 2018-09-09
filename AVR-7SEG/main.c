/*
 * main.c
 *
 * Created: 9/4/2018 1:50:34 PM
 * Author : AHMAD HEGAZY
 */ 


#include <avr/io.h>
#include <stdint.h>

#define SET_BITS(ADDRESS,MASK) (ADDRESS) |= (MASK)
#define CLR_BITS(ADDRESS,MASK) (ADDRESS) &= ~(MASK)
/* this will be zero if the bit is zero, non zero if the bit is one 
	if used with multiple bits ... it can only indicate if all the bits are zeros
*/
#define GET_BITS(ADDRESS,MASK) ((ADDRESS) & (MASK))

void reset(void);
void delay(void){
	
	volatile uint32_t i;
	for (i=0;i<50000;i++);

}

int main(void)
{
	uint8_t count = 0;
	/*
		PORTD 0 , 1 , 2 : buttons 
		PORTC 7,6,5,4 : 7 SEG, A B C D | pin 2, 7 SEG Enable
	*/
	
	/* PORTD [0,1,2] pins: input */
	
	CLR_BITS(DDRD,0x07); /* DDRD &= ~ 0x07; *//* ~( 111 << 5); */ /* data direction input for pins 0,1,2 port D : 0 input, 1 output */ // mask : 0000 0111 : 0x07


	#if 0
	/* the buttons doesnot need a pullup resistor, they are active high 
		but here is the implementation if needed.
	*/
	SET_BITS(PORTD,0x07); /* PORTD |= 0x07; *//* ( 111 << 5);*/ /* pull up resistor enable for pins 0,1,2 port D*/
	#endif

	/* PORTC output for 7 SEG */
	SET_BITS(DDRC,0xf4); // DDRC |= 0xf4; /* last 4 bits and enable bit should be 1 | mask: 1111 0100 : 0xf4 */
	SET_BITS(PORTC,0x04);// PORTC |= 0x04;/* Enable 7 seg : bit # 3 | mask : 0000 0100 : 0x04*/

	while (1) 
    {
		/*
			check if button 0 is pressed , button 1 is pressed , button 2 is pressed
			PORTD PINS 0 up ,1 down ,2 reset 
		*/
		if( GET_BITS(PIND,0x01) != 0x00 ){ /* PIND & 0x01 reading PORT D PIN 5 value = 0 // button is clicked | mask: 0000 0001 : 0x01 */

			if ( count == 9 ){
				count = 0;
				reset();
			}else {
				count++;
				reset();
				SET_BITS(PORTC,count << 4); /* PORTC |= (count << 4); *//* 0001 0000 */
			}
			delay();
		}
		if( GET_BITS(PIND,0x02) != 0x00 ){ /* PIND & 0x02 reading PORT D PIN 6 value = 0 // button is clicked | mask: 0000 0010 : 0x02 */
			if( count == 0 ){
					count = 9;
				}else {
					count--;
				}
				reset();
				SET_BITS(PORTC,count << 4);/*PORTC |= (count << 4);*/
				
			delay();
		}
		if( GET_BITS(PIND,0x04) != 0x00 ){ /* PIND & 0x04 reading PORT D PIN 7 value = 0 // button is clicked | mask: 0000 0100 : 0x04 */
			/* reset */
			count = 0;
			reset();
			delay();
		}
    }
}

void reset(void){
	CLR_BITS(PORTC,0xf0);
}

