#ifndef SETUP_C
#define SETUP_C

#include "setup_simulation.h"
#include "matrix.h"
#include "agents.h"
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

#endif