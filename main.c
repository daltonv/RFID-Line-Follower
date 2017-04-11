
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
#include "delay.h"
#include "pathfinding.h"

void propCtrl();
void followDirections();
void shortestPath();
void findEnd();
int handleIntersection(int cmd, int i);
void stopAtIntersection();
void turnAround();
void flashLED();

const int paths[4][15] = {
                   {FORWARD,RIGHT,FINDEND,SWITCH,WAIT,LEFT,FORWARD,STOP,SWITCH,END},
                   {FORWARD,FORWARD,LEFT,STOP,0,0,0,0,0},
                   {LEFT,RIGHT,RIGHT,FORWARD,FINDEND,0,0,0,0},
                   {FORWARD,LEFT,STOP,WAIT,LEFT,LEFT,LEFT,END}
};
int curVertex = 3;
int face = FORWARD;

const int maxSpeed = 1500;
const float lineSpeedSlope = maxSpeed/4.5;



int main(void) {
    SystemInit(); //24MHz Clock

    motors_init();
    line_sensor_init();
    rfid_init();

    int mclk = CS_getMCLK();

    irOn();

    //start with no speed
    straight(0);

    int ID = 0;

    while(1)
    {
        ID = 0;

        //get shortest distance ready for all vertexes
        dijikstra(curVertex);

        ID = getID();

        if(ID == 363562828) {
            shortestPath(7); //(1,3) //card 3
            //flashLED();
        }
        else if (ID == 363561852) {
            shortestPath(2); //(0,1) card 2
        }
        else if (ID == 367653260) {
            shortestPath(5); //(2,2) card 4
        }
        else if (ID == 6054415) {
            shortestPath(0); //(1,0) card 1
        }
        else if (ID == 3918753) {
            shortestPath(6); //(0,3) card 5
        }

        delay_ms(100);
    }
}

void followDirections(int col) {
    int i = 0;

    while(paths[col][i] != END) {
        int cmd = paths[col][i];

        if(cmd == LEFT || cmd == RIGHT || cmd == FORWARD) {
            i = handleIntersection(cmd, i);
        }
        else if(cmd == FINDEND) {
            findEnd();
            i++;
        }
        else if(cmd == SWITCH) {
            turnAround();
            i++;
        }
        else if(cmd == WAIT) {
            straight(0);
            delay_ms(2000);

            i++;
        }
        else if(cmd == STOP) {
            stopAtIntersection();
            i++;
        }

    }

    delay_ms(500);

    //stop
    straight(0);

    return;
}

void shortestPath(int vertex) {
    getPath(vertex);
    getDirections();

    int index = 0;

    while(index != path_index-1) {
        int norm_dir = directions[index];
        int dir = 0;

        int f = FORWARD;
        int l = LEFT;
        int r = RIGHT;
        int b = BACKWARD;

        if(face == LEFT) {
            f = RIGHT;
            l = FORWARD;
            r = BACKWARD;
            b = LEFT;
        }
        else if(face == RIGHT) {
            f = LEFT;
            l = BACKWARD;
            r = FORWARD;
            b = RIGHT;
        }
        else if(face == BACKWARD) {
            f = BACKWARD;
            l = RIGHT;
            r = LEFT;
            b = FORWARD;
        }

        if(norm_dir == FORWARD) {
            dir = f;
        }
        else if(norm_dir == LEFT) {
            dir = l;
        }
        else if(norm_dir == RIGHT) {
            dir = r;
        }
        else if(norm_dir == BACKWARD) {
            dir = b;
        }

        face = norm_dir;

        if(dir == BACKWARD) {
            turnAround();
            index++;
        }
        else {
            int i = 0;
            while(!i) {
                i = handleIntersection(dir,i);
            }
            index++;
        }

    }

    path_index = 0;

    stopAtIntersection();
    straight(0);

    curVertex = vertex;
}

int handleIntersection(int cmd, int i) {
    int edge = getEdge();
    if(edge == EDGE_NONE || edge == EDGE_STRAIGHT || edge == NO_LINE) {
        propCtrl();
    }
    else {
        straight(0);
        delay_ms(1000);
        straight(maxSpeed);

        if(cmd == LEFT || cmd == RIGHT) {
            straight(0);
            turn(cmd,maxSpeed);
            edge = getEdge();
            while(edge != EDGE_STRAIGHT) {
                edge = getEdge();

            }
        }
        else {
            delay_ms(1000);
        }
        i++;
    }

    return i;
}

void findEnd() {
    int edge = 0;
    while(edge != NO_LINE) {
        propCtrl();
        edge = getEdge();
    }
    delay_ms(1000);

    return;
}

void turnAround() {
    turnInPlace(LEFT, 800);
    delay_ms(2500);

    float line;
    int edge;

    while(1) {
        line = readLineAvg();
        edge = getEdge();

        if (line == 4.5 && edge == EDGE_STRAIGHT) {
            break;
        }
    }

    straight(0);

    return;
}

void stopAtIntersection() {
    int edge = EDGE_STRAIGHT;
    while(edge == EDGE_NONE || edge == EDGE_STRAIGHT || edge == NO_LINE) {
        propCtrl();
        edge = getEdge();
    }

    return;
}

void propCtrl() {
    float line = readLineAvg();

    /*
    int leftSpeed = line*lineSpeedSlope + .5;
    int rightSpeed = (9-line)*lineSpeedSlope + .5;

    if (rightSpeed > maxSpeed) {
        rightSpeed = maxSpeed;
    }
    if (leftSpeed > maxSpeed) {
        leftSpeed = maxSpeed;
    }
    */
    int Gain = 500;
    int rightSpeed = maxSpeed - Gain * (line - 4.5);
    int leftSpeed = maxSpeed + Gain * (line - 4.5);

    setLeftSpeed(1,leftSpeed);
    setRightSpeed(1,rightSpeed);

    return;
}

void flashLED() {
    MAP_ADC14_disableInterrupt(ADC_INT7);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);

    for(int i = 0; i<20 ; i++) {
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN5);
        delay_ms(500);
    }

    return;
}

