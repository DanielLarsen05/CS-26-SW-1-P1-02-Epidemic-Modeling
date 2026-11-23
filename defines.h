#ifndef DEFINES_H
#define DEFINES_H

#define POPULATION 40
#define MATRIX_SIZE_X 8
#define MATRIX_SIZE_Y 8
#define TRANSMISSION_RISK_PERCENT 10
#define EMPTY -1
#define INFECTION_DURATION 10
#define TIMESTEP 1
#define MAX_SIMULATION_TIMESTEPS 1000

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
    int infectionTime;
    Position position;
    Position hub1;
    Position hub2;
    Position target;
} Agent;

extern int matrix[MATRIX_SIZE_X][MATRIX_SIZE_Y];
extern Agent agents[POPULATION];
extern int currentTime;

#endif
