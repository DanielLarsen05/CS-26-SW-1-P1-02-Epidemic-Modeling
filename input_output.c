#ifndef INPUT_OUTPUT_C
#define INPUT_OUTPUT_C
#include "input_output.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void printDataToFile(FILE* f){
    int countOfSusceptible = getSusceptibleCount();
    int countOfInfected = getInfectedCount();
    int countOfRecovered = getRecoveredCount();
    fprintf(f, "S = %d, I = %d, R = %d\n", countOfSusceptible, countOfInfected, countOfRecovered);
}

#endif