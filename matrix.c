#ifndef MATRIX_C
#define MATRIX_C
#include "defines.h"
#include "agents.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void printMatrixIndex(int* matrix, int currentTime){
    printf("Time: %d\n", currentTime);
    for(int y=0;y<MATRIX_SIZE_Y;y++){
        if(y==0){
            printf("|");
        } else{
            printf("\n|");
        }
        for(int x=0;x<MATRIX_SIZE_X;x++){
            Position currentPosition = {x, y};
            int agentIndex = getMatrixValue(currentPosition, matrix);
            printf("%2d|", agentIndex);
        }
    }
    printf("\n\n");
}

void printMatrix(int* matrix, Agent* agents, int currentTime){
    printf("Time: %d\n", currentTime);
    for(int y=0;y<MATRIX_SIZE_Y;y++){
        if(y==0){
            printf("|");
        } else{
            printf("\n|");
        }
        for(int x=0;x<MATRIX_SIZE_X;x++){
            Position currentPosition = {x, y};
            int agentIndex = getMatrixValue(currentPosition, matrix);
            if(agentIndex == EMPTY){
                printf(" |");
                continue;
            }
            Agent agent = agents[agentIndex];
            State state = agent.state;
            switch (state)
            {
            case SUSCEPTIBLE:
                printf("S|");
                break;
            case INFECTED:
                printf("I|");
                break;
            case RECOVERED:
                printf("R|");
                break;
            }
        }
    }
    printf("\n\n");
}

void resetMatrix(int* matrix){
    for(int x=0;x<MATRIX_SIZE_X;x++){
        for(int y=0;y<MATRIX_SIZE_Y;y++){
            Position currentPosition = {x, y};
            setMatrixValue(currentPosition, EMPTY, matrix);
        }
    }
}

Position getRandomPosition(){
    int randomX = rand() % MATRIX_SIZE_X;
    int randomY = rand() % MATRIX_SIZE_Y;
    Position randomPosition = {randomX, randomY};
    return randomPosition;
}

Position getRandomEmptyPosition(int* matrix){
    Position randomPosition = getRandomPosition();
    while(getMatrixValue(randomPosition, matrix) != EMPTY){
        randomPosition = getRandomPosition();
    }
    return randomPosition;
}

int getMatrixValue(Position position, int* matrix){
    return matrix[position.x+MATRIX_SIZE_X*position.y];
}

void setMatrixValue(Position position, int value, int* matrix){
    matrix[position.x+MATRIX_SIZE_X*position.y] = value;
}

int getInfectedCount(Agent* agents){
    int infectedCount=0;
    for (int agentIndex=0; agentIndex<POPULATION; agentIndex++) {
        if (agents[agentIndex].state == INFECTED){
            infectedCount++;
        }
    }
    return infectedCount;
}

int getSusceptibleCount(Agent* agents){
    int susceptibleCount=0;
    for (int agentIndex=0; agentIndex<POPULATION; agentIndex++) {
        if (agents[agentIndex].state == SUSCEPTIBLE){
            susceptibleCount++;
        }
    }
    return susceptibleCount;
}

int getRecoveredCount(Agent* agents){
    int recoveredCount=0;
    for (int agentIndex=0; agentIndex<POPULATION; agentIndex++) {
        if (agents[agentIndex].state == RECOVERED){
            recoveredCount++;
        }
    }
    return recoveredCount;
}

#endif