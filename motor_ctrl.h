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

#define LEFT 0
#define RIGHT 1
#define TIMER_PERIOD 2000

void motors_init();

void straight(int speed);
void turnInPlace(int dir, int speed);
void setLeftSpeed(int dir, int speed);
void setRightSpeed(int dir, int speed);


#endif /* MOTOR_CTRL_H_ */
