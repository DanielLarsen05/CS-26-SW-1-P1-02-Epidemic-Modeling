#include "defines.h"
#include "setup_simulation.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

State matrix[MATRIX_SIZE_X][MATRIX_SIZE_Y];
Position agentPositions[POPULATION];

int main(){
    setupSimulation();
    printMatrix();
    return EXIT_SUCCESS;
}