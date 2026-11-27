#ifndef AGENTS_H
#define AGENTS_H
#include "defines.h"

void moveAgent(Agent* agent, int* matrix);

void moveAgents(int* matrix, Agent* agents);

void switchTarget(Agent* agent);

int compareTwoPositions(Position position1, Position position2);

void spawnAgents(int* matrix, Agent* agents);

void runVaccination(Agent* agents, int currentTime);

void runRecovery(Agent* agents, int currentTime);

void runTransmissions(int* matrix, Agent* agents, int currentTime);

void getInfectedNeighborCount(const Agent* agent, int* matrix, Agent* agents, int currentTime, int* infectedMaskCount, int* infectedNoMaskCount);

State getInfection(int infectedMaskCount, int infectedNoMaskCount);

#endif
