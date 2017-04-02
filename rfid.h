/*
 * rfid.h
 *
 *  Created on: Apr 2, 2017
 *      Author: dalto
 */

#ifndef RFID_H_
#define RFID_H_

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void rfid_init();
int getID();


#endif /* RFID_H_ */
