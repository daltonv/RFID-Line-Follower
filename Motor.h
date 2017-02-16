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

#define TIMER_PERIOD 1000

class Motor
{
public:
    Motor(unsigned int port0, unsigned int pin0, unsigned int port1, unsigned int pin1);
    virtual ~Motor();

    unsigned int port0;
    unsigned int pin0;
    unsigned int port1;
    unsigned int pin1;

    void setDir(unsigned int dir);
};

#endif /* MOTOR_H_ */
