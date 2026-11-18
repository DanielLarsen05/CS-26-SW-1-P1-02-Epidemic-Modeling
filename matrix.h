#ifndef MATRIX_H
#define MATRIX_H

#include "defines.h"

void printMatrix();

void resetMatrix();

Position getRandomPosition();

Position getRandomEmptyPosition();

int getInfectedCount();

int getSusceptibleCount();

int getRecoveredCount();

#endif