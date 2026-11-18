#include "defines.h"
#include "simulation.h"
#include "matrix.h"
#include "agents.h"
#include "input_output.h"
#include <stdio.h>
#include <stdlib.h>

int matrix[MATRIX_SIZE_X][MATRIX_SIZE_Y];
Agent agents[POPULATION];

int main(){
    setupSimulation();
    FILE* file = fopen("Output/data.txt", "w");
    if(file == NULL){
        printf("Could not open file Output/data.txt");
        exit(EXIT_FAILURE);
    }
    printDataToFile(file);
    fclose(file);
    //runSimulation();
    return EXIT_SUCCESS;
}