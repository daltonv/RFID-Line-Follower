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
     TIMER_PERIOD,
     TIMER_A_CAPTURECOMPARE_REGISTER_1,
     TIMER_A_OUTPUTMODE_RESET_SET,
     1000
};

Timer_A_PWMConfig pwmConfigL_2 =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_24,
     TIMER_PERIOD,
     TIMER_A_CAPTURECOMPARE_REGISTER_2,
     TIMER_A_OUTPUTMODE_RESET_SET,
     1000
};

Timer_A_PWMConfig pwmConfigR_1  =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_24,
     TIMER_PERIOD,
     TIMER_A_CAPTURECOMPARE_REGISTER_3,
     TIMER_A_OUTPUTMODE_RESET_SET,
     1000
};

Timer_A_PWMConfig pwmConfigR_2 =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_24,
     TIMER_PERIOD,
     TIMER_A_CAPTURECOMPARE_REGISTER_4,
     TIMER_A_OUTPUTMODE_RESET_SET,
     1000
};


void motors_init() {
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5 + GPIO_PIN4 + GPIO_PIN6 + GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigL_1);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigL_2);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigR_1);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigR_2);
}

void straight(int speed) {
    setLeftSpeed(1,speed);
    setRightSpeed(1,speed);
}

void turnInPlace(int dir, int speed) {
    if (dir == LEFT) {
        setLeftSpeed(1,speed);
        setRightSpeed(0,speed);
    }
    else {
        setLeftSpeed(0,speed);
        setRightSpeed(1,speed);
    }
}

void turn(int dir, int speed) {
    if (dir == LEFT) {
        setLeftSpeed(1,speed);
        setRightSpeed(1,0);
    }
    else {
        setLeftSpeed(1,0);
        setRightSpeed(1,speed);
    }
}

void setLeftSpeed(int dir ,int speed) {
    if (dir == 1) {
        TA0CCR1 = 0;
        TA0CCR2 = speed;
    }
    else {
        TA0CCR1 = speed;
        TA0CCR2 = 0;
    }

    /* Initialize compare registers to generate PWM1 */
    //MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigL_1);
    //MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigL_2);
}

void setRightSpeed(int dir, int speed) {
    if (dir == 1) {
        TA0CCR3 = 0;
        TA0CCR4 = speed;
    }
    else {
        TA0CCR3 = speed;
        TA0CCR4 = 0;
    }

    /* Initialize compare registers to generate PWM1 */
    //MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigR_1);
    //MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigR_2);
}
