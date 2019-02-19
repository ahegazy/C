/*
 * delay.c
 *
 *  Created on: Feb 18, 2019
 *      Author: AHMAD HEGAZY <https://ahegazy.github.io>
 */

/*
 * TIVAC TM4C123 is working on 16MHz clock frequency
 * */

#include "delay.h"

/* multiple of millisecond/MicroSec delay using periodic mode
 * 1: Milli seconttimed, 0 Micro Sec */
void timer0A_delay(uint32_t time, delayType type)
{
    uint32_t i;
    SYSCTL_RCGCTIMER_R |= 0x01;     /* enable clock to Timer Block 0 */

    TIMER0_CTL_R = 0;            /* disable Timer before initialization */
    TIMER0_CFG_R = 0x04;         /* 16-bit option */
    TIMER0_TAMR_R = 0x02;        /* periodic mode and down-counter 0000 0010 */
    TIMER0_TAILR_R = type ? (16000 - 1) : (16 - 1);  /* Timer A interval load value register */
    TIMER0_ICR_R = 0x1;          /* clear the TimerA timeout flag*/
    TIMER0_CTL_R |= 0x01;        /* enable Timer A after initialization */

    for(i = 0; i < time; i++) {
        while ((TIMER0_RIS_R & 0x1) == 0) ;      /* wait for TimerA timeout flag */
        TIMER0_ICR_R = 0x1;      /* clear the TimerA timeout flag */
    }

}
