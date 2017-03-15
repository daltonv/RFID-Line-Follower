
/*
 * -------------------------------------------
 *    MSP432 DriverLib - v3_50_00_02 
 * -------------------------------------------
 *
 * --COPYRIGHT--,BSD,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/******************************************************************************
 * MSP432 Empty Project
 *
 * Description: An empty project that uses DriverLib
 *
 *                MSP432P401
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST               |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 * Author: 
*******************************************************************************/
#define __NOP __nop

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "LineSensor.h"
#include "MotorControl.h"

void testPropCtrl();

int maxSpeed = 910;
const float lineSpeedSlope = (float)maxSpeed/4.5;

MotorControl motorTest;
LineSensor lineTest;

int main(void) {
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    /* Setting DCO to 24MHz */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    lineTest.irOn();

    while(1)
    {
        testPropCtrl();
    }
}

void testPropCtrl() {
    float line = lineTest.readLineAvg();
    int leftSpeed = floor(line*lineSpeedSlope + .5);
    int rightSpeed = floor((9-line)*lineSpeedSlope + .5);

    /* this should be in the motor control code */
    if (rightSpeed > maxSpeed) {
        rightSpeed = maxSpeed;
    }
    if (leftSpeed > maxSpeed) {
        leftSpeed = maxSpeed;
    }

    motorTest.setLeftSpeed(leftSpeed);
    motorTest.setRightSpeed(rightSpeed);
}

