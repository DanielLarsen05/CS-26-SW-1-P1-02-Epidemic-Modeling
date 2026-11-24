#include "defines.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int matrix[MATRIX_SIZE_X*MATRIX_SIZE_Y];
    Agent agents[POPULATION];
    int currentTime=0;
    srand(time(NULL));
    setupSimulation(matrix, agents, &currentTime);
    runSimulation(matrix, agents, &currentTime);
    return EXIT_SUCCESS;
}