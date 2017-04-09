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

#define EDGE_NONE 0
#define EDGE_LEFT 1
#define EDGE_RIGHT 2
#define EDGE_BOTH 3
#define EDGE_STRAIGHT 4
#define NO_LINE 5

void line_sensor_init();

void irOff();
void irOn();
int detectEdge();
float readLineAvg();

#endif /* LINE_SENSOR_H_ */
