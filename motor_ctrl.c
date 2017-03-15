/*
 * motor.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: dalton
 */

#include <motor_ctrl.h>

Timer_A_PWMConfig pwmConfigL_1  =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_24,
     1000,
     TIMER_A_CAPTURECOMPARE_REGISTER_1,
     TIMER_A_OUTPUTMODE_RESET_SET,
     1000
};

Timer_A_PWMConfig pwmConfigL_2 =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_24,
     1000,
     TIMER_A_CAPTURECOMPARE_REGISTER_2,
     TIMER_A_OUTPUTMODE_RESET_SET,
     1000
};

Timer_A_PWMConfig pwmConfigR_1  =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_24,
     1000,
     TIMER_A_CAPTURECOMPARE_REGISTER_3,
     TIMER_A_OUTPUTMODE_RESET_SET,
     1000
};

Timer_A_PWMConfig pwmConfigR_2 =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_24,
     1000,
     TIMER_A_CAPTURECOMPARE_REGISTER_4,
     TIMER_A_OUTPUTMODE_RESET_SET,
     1000
};


void motors_init() {
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5 + GPIO_PIN4 + GPIO_PIN6 + GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
}

void straight(int speed) {
    setLeftSpeed(speed);
    setRightSpeed(speed);
}

void turnInPlace(int dir, int speed) {
    if (dir == LEFT) {
        setLeftSpeed(speed);
        setRightSpeed(-1*speed);
    }
    else {
        setLeftSpeed(-1*speed);
        setRightSpeed(speed);
    }
}

void setLeftSpeed(int speed) {
    if (speed > 0) {
        pwmConfigL_1.dutyCycle = 0;
        pwmConfigL_2.dutyCycle = speed;
    }
    else {
        speed = speed * -1;
        pwmConfigL_1.dutyCycle = speed;
        pwmConfigL_2.dutyCycle = 0;
    }

    /* Initialize compare registers to generate PWM1 */
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigL_1);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigL_2);
}

void setRightSpeed(int speed) {
    if (speed > 0) {
        pwmConfigR_1.dutyCycle = 0;
        pwmConfigR_2.dutyCycle = speed;
    }
    else {
        speed = speed * -1;
        pwmConfigR_1.dutyCycle = speed;
        pwmConfigR_2.dutyCycle = 0;
    }

    /* Initialize compare registers to generate PWM1 */
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigR_1);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigR_2);
}
