#ifndef SETUP_H
#define SETUP_H
#include "defines.h"

void setupSimulation(int* matrix, Agent* agents, int* currentTime);

void iterateSimulation(int* matrix, Agent* agents, int* currentTime);

void runSimulation(int* matrix, Agent* agents, int* currentTime);

#endif