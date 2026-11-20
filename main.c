#include "defines.h"
#include "simulation.h"
#include "matrix.h"
#include "agents.h"
#include "input_output.h"
#include <stdio.h>
#include <stdlib.h>

int matrix[MATRIX_SIZE_X][MATRIX_SIZE_Y];
Agent agents[POPULATION];
int time=0;

int main(){
    setupSimulation();
    runSimulation();
    return EXIT_SUCCESS;
}