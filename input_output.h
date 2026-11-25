#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H
#include "defines.h"
#include <stdio.h>

void setupDataFile(FILE* f);

void printDataToFile(FILE* f, Agent* agents);

#endif