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
#include "delay.h"

#define RIGHT 1
#define LEFT 2
#define FORWARD 3
#define BACKWARD 4
#define STOP 5
#define FINDEND 6
#define SWITCH 7
#define END 8
#define WAIT 9

#define TIMER_PERIOD 2500

void motors_init();

void straight(int speed);
void turnInPlace(int dir, int speed);
void turn(int dir, int speed);
void setLeftSpeed(int dir, int speed);
void setRightSpeed(int dir, int speed);


#endif /* MOTOR_CTRL_H_ */
