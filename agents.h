#ifndef AGENTS_H
#define AGENTS_H
#include "defines.h"

void moveAgent(Agent agent);

void moveAgents();

void spawnAgents();

void runTransmissions();

int getInfectedNeighborCount(Agent agent);

State getInfection(int infectedCount);

#endif