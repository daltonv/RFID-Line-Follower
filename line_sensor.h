/*
 * linefollower.h
 *
 *  Created on: Jan 19, 2017
 *      Author: dalto
 */

#ifndef LINE_SENSOR_H_
#define LINE_SENSOR_H_

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void line_sensor_init();

void irOff();
void irOn();
float readLineAvg();

#endif /* LINE_SENSOR_H_ */
