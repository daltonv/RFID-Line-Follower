/*
 * pathfinding.h
 *
 *  Created on: Apr 8, 2017
 *      Author: dalto
 */

#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include <string.h>
#include "motor_ctrl.h"

#define V 9

extern int directions[V];
extern int path_index;

void dijikstra(int src);
int minDistance(int dist[], int sptSet[]);
void getPath(int dest);
void getDirections();

#endif /* PATHFINDING_H_ */
