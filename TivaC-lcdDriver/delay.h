/*
 * delay.h
 *
 *  Created on: Feb 18, 2019
 *      Author: AHMAD HEGAZY <https://ahegazy.github.io>
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "hw_gpio.h"
#include <stdint.h>

typedef enum delayType {Micro = 0, Milli = 1} delayType;
void timer0A_delay(uint32_t time,delayType type);

#define delay_ms(t) timer0A_delay(t, Milli)
#define delay_us(t) timer0A_delay(t, Micro)



#endif /* DELAY_H_ */
