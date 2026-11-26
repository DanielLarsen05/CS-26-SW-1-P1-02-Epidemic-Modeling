#ifndef MATRIX_H
#define MATRIX_H

#include "defines.h"

void printMatrixIndex(int* matrix, int currentTime);

void printMatrix(int* matrix, Agent* agents, int currentTime);

void resetMatrix(int* matrix);

Position getRandomPosition();

Position getRandomEmptyPosition(int* matrix);

int getMatrixValue(Position position, int* matrix);
void setMatrixValue(Position position, int value, int* matrix);

int getInfectedCount(Agent* agents);

int getSusceptibleCount(Agent* agents);

int getRecoveredCount(Agent* agents);

int getVaccinatedCount(Agent* agents);

#endif