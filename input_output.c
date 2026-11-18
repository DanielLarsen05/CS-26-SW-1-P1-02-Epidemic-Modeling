#ifndef INPUT_OUTPUT_C
#define INPUT_OUTPUT_C
#include "input_output.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void printDataToFile(FILE* f){
    int countOfSusceptible = susceptibleCount();
    int countOfInfected = infectedCount();
    int countOfRecovered = recoveredCount();
    fprintf(f, "S = %d, I = %d, R = %d\n", countOfSusceptible, countOfInfected, countOfRecovered);
}

#endif