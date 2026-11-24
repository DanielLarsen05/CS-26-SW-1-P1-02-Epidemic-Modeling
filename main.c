#include "defines.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    //define the matrix size for our simulations, create the array needed for our Agent management,
    //and start the simulation timer
    int matrix[MATRIX_SIZE_X*MATRIX_SIZE_Y];
    Agent agents[POPULATION];
    int currentTime=0;
    // it then instantiates the random seed based on the computer clock(?)
    srand(time(NULL));
    // we then do the setup for the simulation before running it to completion
    setupSimulation(matrix, agents, &currentTime);
    runSimulation(matrix, agents, &currentTime);
    return EXIT_SUCCESS;
}