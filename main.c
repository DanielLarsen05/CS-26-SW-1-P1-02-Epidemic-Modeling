#include "defines.h"
#include "setup_simulation.h"
#include "matrix.h"
#include "agents.h"
#include <stdio.h>
#include <stdlib.h>

int matrix[MATRIX_SIZE_X][MATRIX_SIZE_Y];
Agent agents[POPULATION];

int main(){
    setupSimulation();
    printMatrix();
    return EXIT_SUCCESS;
}