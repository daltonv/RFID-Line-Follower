/*
 * motor.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: dalton
 */

#include <motor_ctrl2.h>

const Timer_A_UpDownModeConfig upDownConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock SOurce
        TIMER_A_CLOCKSOURCE_DIVIDER_24,         // SMCLK/4 = 3MHz
        1000,                                   // 127 tick period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
};

Timer_A_CompareModeConfig   NpwmConfigL_1  =
{
    TIMER_A_CAPTURECOMPARE_REGISTER_1,          // Use CCR1
    TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
    TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
    1000                                // duty cycle initialized to 0
};

Timer_A_CompareModeConfig   NpwmConfigL_2 =
{
    TIMER_A_CAPTURECOMPARE_REGISTER_2,          // Use CCR2
    TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
    TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
    1000                                // duty cycle initialized to 0
};

Timer_A_CompareModeConfig   NpwmConfigR_1  =
{
    TIMER_A_CAPTURECOMPARE_REGISTER_3,          // Use CCR3
    TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
    TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
    1000                                // duty cycle initialized to 0
};

Timer_A_CompareModeConfig   NpwmConfigR_2 =
{
    TIMER_A_CAPTURECOMPARE_REGISTER_4,          // Use CCR4
    TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
    TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
    1000                                // duty cycle initialized to 0
};


void Nmotors_init() {
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5 + GPIO_PIN4 + GPIO_PIN6 + GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring Timer_A1 for UpDown Mode and starting */
    MAP_Timer_A_configureUpDownMode(TIMER_A1_BASE, &upDownConfig);
    MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UPDOWN_MODE);


    /* Initialize compare registers to generate PWM1 */
    MAP_Timer_A_initCompare(TIMER_A0_BASE, &NpwmConfigL_1);
    MAP_Timer_A_initCompare(TIMER_A0_BASE, &NpwmConfigL_2);
    MAP_Timer_A_initCompare(TIMER_A0_BASE, &NpwmConfigR_1);
    MAP_Timer_A_initCompare(TIMER_A0_BASE, &NpwmConfigR_2);
}

void Nstraight(int speed) {
    setLeftSpeed(1,speed);
    setRightSpeed(1,speed);
}

void NturnInPlace(int dir, int speed) {
    if (dir == 1) {
        setLeftSpeed(1,speed);
        setRightSpeed(0,speed);
    }
    else {
        setLeftSpeed(1,speed);
        setRightSpeed(0,speed);
    }
}

void NsetLeftSpeed(int dir ,int speed) {
    if (dir == 1) {
        TA0CCR1 = 0;
        TA0CCR2 = speed;
    }
    else {
        TA0CCR1 = speed;
        TA0CCR2 = 0;
    }
}

void NsetRightSpeed(int dir, int speed) {
    if (dir == 1) {
        TA0CCR3 = 0;
        TA0CCR4 = speed;
    }
    else {
        TA0CCR3 = speed;
        TA0CCR4 = 0;
    }
}
