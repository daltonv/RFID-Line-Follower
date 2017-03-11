/*
 * linefollower.h
 *
 *  Created on: Jan 19, 2017
 *      Author: dalto
 */

#ifndef LINESENSOR_H_
#define LINESENSOR_H_

#define __NOP __nop
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

class LineSensor
{
public:
    LineSensor();
    virtual ~LineSensor();

    void irOff();
    void irOn();
};

#endif /* LINESENSOR_H_ */
