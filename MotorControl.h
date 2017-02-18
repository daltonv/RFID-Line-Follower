/*
 * MotorControl.h
 *
 *  Created on: Jan 26, 2017
 *      Author: dalto
 */

#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#define __NOP __nop
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "Motor.h"

class MotorControl
{
public:
    MotorControl();
    virtual ~MotorControl();

    Motor leftMotor;
    Motor rightMotor;

    straight(int speed);
};

#endif /* MOTORCONTROL_H_ */
