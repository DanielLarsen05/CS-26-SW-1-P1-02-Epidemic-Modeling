#ifndef INPUT_OUTPUT_C
#define INPUT_OUTPUT_C
#include "input_output.h"
#include "matrix.h"
#include "defines.h"
#include <stdio.h>

void setupDataFile(FILE* f){
    fprintf(f, "Susceptible,Infected,Recovered\n");
}

void printDataToFile(FILE* f, Agent* agents){
    int countOfSusceptible = getSusceptibleCount(agents);
    int countOfInfected = getInfectedCount(agents);
    int countOfRecovered = getRecoveredCount(agents);
    int countOfVaccinated = getVaccinatedCount(agents);
    fprintf(f, "%d,%d,%d,%d\n", countOfSusceptible, countOfInfected, countOfRecovered, countOfVaccinated);
}

#endif