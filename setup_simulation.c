#ifndef SETUP_C
#define SETUP_C

#include "setup_simulation.h"
#include <stdlib.h>
#include <stdio.h>

void setupSimulation(){
    //Check if we are all idiots
    if(POPULATION > MATRIX_SIZE_X*MATRIX_SIZE_Y){
        printf("Population is above total number of elements in the matrix.\n");
        exit(EXIT_FAILURE);
    }
    resetMatrix();
    spawnAgents();
}

void resetMatrix(){
    for(int x=0;x<MATRIX_SIZE_X;x++){
        for(int y=0;y<MATRIX_SIZE_Y;y++){
            matrix[x][y] = EMPTY;
        }
    }
}

Position getRandomEmptyPosition(){
    int randomX = rand() % MATRIX_SIZE_X;
    int randomY = rand() % MATRIX_SIZE_Y;
    while(matrix[randomX][randomY] != EMPTY){
        randomX = rand() % MATRIX_SIZE_X;
        randomY = rand() % MATRIX_SIZE_Y;
    }
    Position randomPosition = {randomX, randomY};
    return randomPosition;
}

void spawnAgents(){
    for(int index=0;index<POPULATION;index++){
        Position randomPosition = getRandomEmptyPosition();
        if(index == 0){
            matrix[randomPosition.x][randomPosition.y] = INFECTED;
        } else{
            matrix[randomPosition.x][randomPosition.y] = SUSCEPTIBLE;
        }
        agentPositions[index] = randomPosition;
    }
}

#endif