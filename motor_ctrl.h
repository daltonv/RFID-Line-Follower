/*
 * motor.h
 *
 *  Created on: Jan 24, 2017
 *      Author: dalton
 */

#ifndef MOTOR_CTRL_H_
#define MOTOR_CTRL_H_

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void motors_init();

void straight(int speed);
void setLeftSpeed(int speed);
void setRightSpeed(int speed);


#endif /* MOTOR_CTRL_H_ */