/*
* Author: Gregory Gutmann
* Nearest neighbor search algorithm demo.
*/

#ifndef HELPER_H
#define HELPER_H

#define PERFORMANCE_TEST 1

#if !PERFORMANCE_TEST
    #define X_DIM 15
    #define Y_DIM 15
    #define CELL_SIZE 5
    #define GRID_BUFFER 5 // two times the cell size is a good starting point
    #define PARTICLE_COUNT 10
#else
    #define X_DIM 100
    #define Y_DIM 100
    #define CELL_SIZE 5
    #define GRID_BUFFER 10 // two times the cell size is a good starting point
    #define PARTICLE_COUNT 800
#endif

struct float2 {
    float x;
    float y;
};

float2 make_float2(float a, float b);

#endif // HELPER_H