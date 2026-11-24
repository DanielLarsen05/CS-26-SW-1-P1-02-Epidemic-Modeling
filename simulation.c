#ifndef SETUP_C
#define SETUP_C

#include "simulation.h"
#include "matrix.h"
#include "agents.h"
#include "input_output.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void setupSimulation(int* matrix, Agent* agents, int* currentTime){
    //Check if we are all idiots
    if(POPULATION > MATRIX_SIZE_X*MATRIX_SIZE_Y){
        printf("Population is above total number of elements in the matrix.\n");
        exit(EXIT_FAILURE);
    }
    *currentTime = 0;
    resetMatrix(matrix);
    spawnAgents(matrix, agents);
}

void iterateSimulation(int* matrix, Agent* agents, int* currentTime){
    srand(time(NULL));
    runRecovery(agents, *currentTime);
    moveAgents(matrix, agents);
    runTransmissions(matrix, agents, *currentTime);
    *currentTime += TIMESTEP;
}

void runSimulation(int* matrix, Agent* agents, int* currentTime){
    FILE* file = fopen("Output/data.txt", "w");
    if(file == NULL){
        printf("Could not open file Output/data.txt");
        exit(EXIT_FAILURE);
    }
    printDataToFile(file, agents);
    printMatrix(matrix, agents, *currentTime);
    while(getInfectedCount(agents) > 0 && *currentTime < MAX_SIMULATION_TIMESTEPS){
        iterateSimulation(matrix, agents, currentTime);
        printMatrix(matrix, agents, *currentTime);
        printDataToFile(file, agents);
    }
    fclose(file);
}

#endif
