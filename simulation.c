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
    //Check if there is enough space for the amount of agents we want to use
    if(POPULATION > MATRIX_SIZE_X*MATRIX_SIZE_Y){
        printf("Population is above total number of elements in the matrix.\n");
        exit(EXIT_FAILURE);
    }
    // sets the current time to 0, completely empties the matrix, and spawns agents into the matrix and Agent array
    *currentTime = 0;
    resetMatrix(matrix);
    spawnAgents(matrix, agents);
}

void iterateSimulation(int* matrix, Agent* agents, int* currentTime){
    // this function moves the simulation forwards by one timestep and accordingly moves the timestep forwards
    srand(time(NULL));
    runRecovery(agents, *currentTime);
    moveAgents(matrix, agents);
    runTransmissions(matrix, agents, *currentTime);
    *currentTime += TIMESTEP;
}

void runSimulation(int* matrix, Agent* agents, int* currentTime){
    //opens the output file to write the results of the simulation into
    FILE* file = fopen("Output/data.txt", "w");
    //checks if the output file is present
    if(file == NULL){
        printf("Could not open file Output/data.txt");
        exit(EXIT_FAILURE);
    }
    // this writes the stats for our agents into the file and then prints the starting matrix into the console
    printDataToFile(file, agents);
    printMatrix(matrix, agents, *currentTime);
    // this is the main loop of the simulation, at the end of the while loop it tests if there are infected left
    // if there are no infected left, or if they simulation has hit the max timesteps, the simulation ends
    while(getInfectedCount(agents) > 0 && *currentTime < MAX_SIMULATION_TIMESTEPS){
        // this moves the simulation forwards one step and prints the matrix to console each step
        iterateSimulation(matrix, agents, currentTime);
        printMatrix(matrix, agents, *currentTime);

        // it then writes the agent data to the output file
        printDataToFile(file, agents);
    }
    // after the simulation has ended, it closes the output file as it is bo longer needed
    fclose(file);
}

#endif
