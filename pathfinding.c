/*
 * pathfinding.c
 *
 *  Created on: Apr 8, 2017
 *      Author: dalto
 */

#include "pathfinding.h"

static int coords[V][2] = {
                     {1,0}, //0
                     {2,0}, //1
                     {0,1}, //2
                     {1,1}, //3
                     {1,2}, //4
                     {2,2}, //5
                     {0,3}, //6
                     {1,3}, //7
                     {2,3}  //8
};

static int graph[V][V] = {
                 // 0 1 2 3 4 5 6 7 8
                   {0,1,0,1,0,0,0,0,0}, // 0
                   {1,0,0,0,0,2,0,0,0}, // 1
                   {0,0,0,1,0,0,2,0,0}, // 2
                   {1,0,1,0,1,0,0,0,0}, // 3
                   {0,0,0,1,0,1,0,1,0}, // 4
                   {0,2,0,0,1,0,0,0,1}, // 5
                   {0,0,2,0,0,0,0,1,0}, // 6
                   {0,0,0,0,1,0,1,0,1}, // 7
                   {0,0,0,0,0,1,0,1,0}  // 8
};

static int parent[V] = {0,0,0,0,0,0,0};

extern int directions[V] = {0,0,0,0,0,0,0,0,0};
extern int path[V] = {0,0,0,0,0,0,0,0,0};
extern int path_index = 0;

void dijikstra(int src) {
    path_index = 0;

    int dist[V];  // The output array. dist[i] will hold
                  // the shortest distance from src to i

    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    int sptSet[V];

    // Initialize all distances as INFINITE and stpSet[] as false
    int i;
    for (i = 0; i < V; i++) {
        parent[src] = -1;
        dist[i] = 999;
        sptSet[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    int count;
    for (count = 0; count < V-1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        int v;
        for (v = 0; v < V; v++) {
            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    path[0] = src;
    path_index = 1;
}

// A utility function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest
// path tree
int minDistance(int dist[], int sptSet[]) {
    // Initialize min value
    int min = 999, min_index;

    int v;
    for (v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

// Function to print shortest path from source to j
// using parent array
void getPath(int dest) {
    // Base Case : If j is source
    if (parent[dest]==-1)
        return;

    getPath(parent[dest]);

    path[path_index] = dest;
    path_index++;
}

void getDirections() {
    memset(directions, 0x00, 9);

    int i;
    for(i = 0; i < path_index; i++) {

        int point1 = path[i];
        int point2 = path[i+1];

        int x = coords[point2][0] - coords[point1][0];
        int y = coords[point2][1] - coords[point1][1];

        if(x == 0 && y > 0) {
            directions[i] = FORWARD;
        }
        else if(x == 0 && y < 0) {
            directions[i] = BACKWARD;
        }
        else if(x > 0 && y == 0) {
            directions[i] = RIGHT;
        }
        else if(x < 0 && y == 0) {
            directions[i] = LEFT;
        }

    }

    return;
}
