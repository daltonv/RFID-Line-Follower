/*
 * linefollower.h
 *
 *  Created on: Jan 19, 2017
 *      Author: dalto
 */

#ifndef LINEFOLLOWER_H_
#define LINEFOLLOWER_H_

#define __NOP __nop
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

class linefollower
{
public:
    linefollower();
    virtual ~linefollower();

    void togglePort();
};

#endif /* LINEFOLLOWER_H_ */
