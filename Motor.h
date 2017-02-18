/*
 * motor.h
 *
 *  Created on: Jan 24, 2017
 *      Author: dalton
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define __NOP __nop
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

class Motor
{
public:
    Motor(uint_fast16_t reg1, uint_fast16_t reg2);
    virtual ~Motor();

    Timer_A_PWMConfig pwmConfig1;
    Timer_A_PWMConfig pwmConfig2;

    void setSpeed(int speed);
};

#endif /* MOTOR_H_ */
