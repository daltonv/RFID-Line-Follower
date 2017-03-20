/*
 * motor_ctrl2.h
 *
 *  Created on: Mar 19, 2017
 *      Author: dalto
 */

#ifndef MOTOR_CTRL2_H_
#define MOTOR_CTRL2_H_

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void Nmotors_init();

void Nstraight(int speed);
void NturnInPlace(int dir, int speed);
void NsetLeftSpeed(int dir, int speed);
void NsetRightSpeed(int dir, int speed);

#endif /* MOTOR_CTRL2_H_ */
