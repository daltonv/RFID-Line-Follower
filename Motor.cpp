/*
 * motor.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: dalton
 */

#include <Motor.h>

Motor::Motor(uint_fast16_t reg1, uint_fast16_t reg2)
{
    pwmConfig1.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    pwmConfig1.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_24;
    pwmConfig1.timerPeriod = 1000;
    pwmConfig1.compareRegister = reg1;
    pwmConfig1.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    pwmConfig1.dutyCycle = 1000;

    pwmConfig2.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    pwmConfig2.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_24;
    pwmConfig2.timerPeriod = 1000;
    pwmConfig2.compareRegister = reg2;
    pwmConfig2.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    pwmConfig2.dutyCycle = 1000;

    /* Initialize compare registers to generate PWM1 */
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig1);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
}

Motor::~Motor()
{
    // TODO Auto-generated destructor stub
}

void Motor::setSpeed(int speed) {
    if (speed > 0) {
        pwmConfig1.dutyCycle = speed;
        pwmConfig2.dutyCycle = 1000;
    }
    else {
        speed = speed * -1;
        pwmConfig1.dutyCycle = 1000;
        pwmConfig2.dutyCycle = speed;
    }

    /* Initialize compare registers to generate PWM1 */
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig1);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
}
