#ifndef DEFINES_H
#define DEFINES_H

#define POPULATION 10
#define MATRIX_SIZE_X 5
#define MATRIX_SIZE_Y 5

typedef enum {
    EMPTY,
    SUSCEPTIBLE,
    INFECTED,
    RECOVERED
} State;

typedef struct {
    int x;
    int y;
} Position;

extern State matrix[MATRIX_SIZE_X][MATRIX_SIZE_Y];
extern Position agentPositions[POPULATION];

#endif