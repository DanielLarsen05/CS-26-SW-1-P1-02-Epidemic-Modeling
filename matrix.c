#ifndef MATRIX_H
#define MATRIX_H
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>

void printMatrix(){
    for(int y=0;y<MATRIX_SIZE_Y;y++){
        if(y==0){
            printf("|");
        } else{
            printf("\n|");
        }
        for(int x=0;x<MATRIX_SIZE_X;x++){
            if(matrix[x][y] == EMPTY){
                printf(" |");
                continue;
            }
            Agent agent = agents[matrix[x][y]];
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

int infectedCount(){
    
}

#endif