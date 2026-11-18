#ifndef SETUP_C
#define SETUP_C

#include "simulation.h"
#include "matrix.h"
#include "agents.h"
#include "input_output.h"
#include <stdlib.h>
#include <stdio.h>

void setupSimulation(){
    //Check if we are all idiots
    if(POPULATION > MATRIX_SIZE_X*MATRIX_SIZE_Y){
        printf("Population is above total number of elements in the matrix.\n");
        exit(EXIT_FAILURE);
    }
    resetMatrix();
    spawnAgents();
}

void iterateSimulation(){
    
}

void runSimulation(){
    FILE* file = fopen("Output/data.txt", "w");
    if(file == NULL){
        printf("Could not open file Output/data.txt");
        exit(EXIT_FAILURE);
    }
    while(infectedCount() > 0){
        iterateSimulation();
        printDataToFile(file);
    }
}

#endif