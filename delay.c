/*
 * delay.c
 *
 *  Created on: Apr 9, 2017
 *      Author: dalto
 */

#include "delay.h"

static int wait = 0;

void delay_ms(int ms) {
    int i;
    for(i = 0; i<ms; i++) {
        delay();
    }
}

/*delay for 1 ms*/
void delay() {
    wait = 1;

    MAP_SysTick_enableModule();
    MAP_SysTick_setPeriod(24000);
    MAP_SysTick_enableInterrupt();

    while(wait == 1);

    MAP_SysTick_disableInterrupt();
}

/* Timer32 ISR */
void SysTick_Handler(void)
{
    wait = 0;
}

