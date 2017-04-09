
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

/* DriverLib Includes */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>


#include "line_sensor.h"
#include "motor_ctrl.h"
#include "rfid.h"

void propCtrl();
void followDirections();

int paths[4][9] = {
                   {FORWARD,RIGHT,FINDEND,0,0,0,0,0,0},
                   {FORWARD,FORWARD,LEFT,STOP,0,0,0,0,0},
                   {LEFT,RIGHT,RIGHT,FORWARD,FINDEND,0,0,0,0},
                   {FORWARD,FORWARD,LEFT,LEFT,LEFT,STOP,0,0,0}
};

const int maxSpeed = 1000;
const float lineSpeedSlope = maxSpeed/4.5;

int face = FORWARD;

int main(void) {
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    /* Setting DCO to 24MHz */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

    MAP_FPU_enableModule();

    MAP_FlashCtl_setWaitState(FLASH_BANK0,2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1,2);

    motors_init();
    line_sensor_init();
    rfid_init();

    irOn();

    //start with no speed
    straight(0);

    //get shortest distance ready for all vertexes
    //dijikstra(0);

    while(1==1)
    {
        int ID = 0;
        int pathChoice = -1;

        ID = getID();

        if(ID == 363562675) {
            pathChoice = 0;
            followDirections(pathChoice);
        }
        else if (ID == 363561852) {
            pathChoice = 1;
            followDirections(pathChoice);
        }
        else if (ID == 24256125) {
            pathChoice = 2;
            followDirections(pathChoice);
        }
        else if (ID == 6054415) {
            pathChoice = 3;
            followDirections(pathChoice);
        }

    }
}

void followDirections(int col) {
    int i = 0;
    int edge = 0;

    while(paths[col][i] != STOP && paths[col][i] != FINDEND) {
        edge = detectEdge();

        if(edge == EDGE_NONE || edge == EDGE_STRAIGHT || edge == NO_LINE) {
            propCtrl();
        }
        else {
            straight(maxSpeed);

            if(paths[col][i] == LEFT || paths[col][i] == RIGHT) {
                straight(0);
                turn(paths[col][i],maxSpeed);
            }

            edge = detectEdge();
            while(edge != EDGE_STRAIGHT) {
                edge = detectEdge();
                if(paths[col][i] == FORWARD) {
                    propCtrl();
                }
            }

            straight(maxSpeed);

            i++;
        }
    }

    if(paths[col][i] == FINDEND) {
        while(edge != NO_LINE) {
            propCtrl();
            edge = detectEdge();
        }

        while(edge != EDGE_STRAIGHT) {
            turnInPlace(LEFT, 500);
            edge = detectEdge();
        }
    }
    else{
        while(edge == EDGE_NONE || edge == EDGE_STRAIGHT || edge == NO_LINE) {
            propCtrl();
            edge = detectEdge();
        }
    }

    //stop
    straight(0);

    while(1==1) {
    }
}

void propCtrl() {
    float line = readLineAvg();

    int leftSpeed = line*lineSpeedSlope + .5;
    int rightSpeed = (9-line)*lineSpeedSlope + .5;

    /* this should be in the motor control code */
    if (rightSpeed > maxSpeed) {
        rightSpeed = maxSpeed;
    }
    if (leftSpeed > maxSpeed) {
        leftSpeed = maxSpeed;
    }

    setLeftSpeed(1,leftSpeed);
    setRightSpeed(1,rightSpeed);
}

