#ifndef DEFINES_H
#define DEFINES_H

#define POPULATION 10
#define MATRIX_SIZE_X 5
#define MATRIX_SIZE_Y 5
#define TRANSMISSION_RATE 2
#define EMPTY -1
#define INFECTION_DURATION 10
#define TIMESTEP 1

int Time = 0;

typedef enum {
    SUSCEPTIBLE,
    INFECTED,
    RECOVERED
} State;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    State state;
    Position position;
    Position hub1;
    Position hub2;
    Position target;
    int infection_time;
} Agent;

extern int matrix[MATRIX_SIZE_X][MATRIX_SIZE_Y];
extern Agent agents[POPULATION];

#endif
