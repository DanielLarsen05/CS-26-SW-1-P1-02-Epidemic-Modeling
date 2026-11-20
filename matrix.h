#ifndef MATRIX_H
#define MATRIX_H

#include "defines.h"

void printMatrix();

void printHubs();

void resetMatrix();

Position getRandomPosition();

Position getRandomEmptyPosition();

int isPositionHub(Position position);

int getInfectedCount();

int getSusceptibleCount();

int getRecoveredCount();

#endif