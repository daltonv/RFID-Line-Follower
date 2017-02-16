/*
 * motor.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: dalton
 */

#include <Motor.h>

const Timer_A_UpDownModeConfig upDownConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock SOurce
        TIMER_A_CLOCKSOURCE_DIVIDER_24,          // SMCLK/4 = 3MHz
        TIMER_PERIOD,                           // 127 tick period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
};

const Timer_A_CompareModeConfig compareConfig_PWM1 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_1,          // Use CCR1
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
        TIMER_PERIOD                                // duty cycle initialized to 0
};

const Timer_A_CompareModeConfig compareConfig_PWM2 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_2,          // Use CCR2
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
        TIMER_PERIOD                                // duty cycle initialized to 0
};

const Timer_A_CompareModeConfig compareConfig_PWM3 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_3,          // Use CCR2
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
        TIMER_PERIOD                                // duty cycle initialized to 0
};

const Timer_A_CompareModeConfig compareConfig_PWM4 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_4,          // Use CCR2
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
        TIMER_PERIOD                                // duty cycle initialized to 0
};

Motor::Motor(unsigned int port0, unsigned int pin0, unsigned int port1, unsigned int pin1)
{
    this->port0 = port0;
    this->pin0 = pin0;
    this->port1 = port1;
    this->pin1 = pin1;

    /* Setting 7.4 - 7.7 as the outputs for PWM */
    //7.7 == CCR1 ; 7.6 == CCR2; 7.5 == CCR3; 7.4 == CCR4
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7, GPIO_PIN5 + GPIO_PIN4+ GPIO_PIN6 + GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

        /* Configuring Timer_A1 for UpDown Mode and starting */
        MAP_Timer_A_configureUpDownMode(TIMER_A1_BASE, &upDownConfig);
        MAP_Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UPDOWN_MODE);


        /* Initialize compare registers to generate PWM1 */
        MAP_Timer_A_initCompare(TIMER_A1_BASE, &compareConfig_PWM1);
        MAP_Timer_A_initCompare(TIMER_A1_BASE, &compareConfig_PWM2);
        MAP_Timer_A_initCompare(TIMER_A1_BASE, &compareConfig_PWM3);
        MAP_Timer_A_initCompare(TIMER_A1_BASE, &compareConfig_PWM4);
}

Motor::~Motor()
{
    // TODO Auto-generated destructor stub
}

void Motor::setDir(unsigned int dir) {

}
