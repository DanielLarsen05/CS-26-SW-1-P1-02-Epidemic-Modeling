#include "defines.h"
#include "simulation.h"
#include "matrix.h"
#include "agents.h"
#include "input_output.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int matrix[MATRIX_SIZE_X][MATRIX_SIZE_Y];
Agent agents[POPULATION];
int currentTime=0;

int main(){
    srand(time(NULL));
    setupSimulation();
    runSimulation();
    return EXIT_SUCCESS;
}