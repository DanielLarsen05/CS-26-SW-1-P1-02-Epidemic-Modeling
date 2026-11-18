#ifndef AGENTS_H
#define AGENTS_H
#include "defines.h"

void moveAgent(Agent agent);

void moveAgents();

void switchTarget(Agent agent);

int compareTwoPositions(Position position1, Position position2);

void spawnAgents();

void runTransmissions();

int getInfectedNeighborCount(Agent agent);

State getInfection(int infectedCount);

#endif