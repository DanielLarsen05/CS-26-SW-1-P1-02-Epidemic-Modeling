#ifndef INPUT_OUTPUT_C
#define INPUT_OUTPUT_C
#include "input_output.h"
#include "matrix.h"
#include "defines.h"
#include <stdio.h>

void printDataToFile(FILE* f, Agent* agents){
    int countOfSusceptible = getSusceptibleCount(agents);
    int countOfInfected = getInfectedCount(agents);
    int countOfRecovered = getRecoveredCount(agents);
    fprintf(f, "S = %d, I = %d, R = %d\n", countOfSusceptible, countOfInfected, countOfRecovered);
}

#endif