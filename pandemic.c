#include <stdio.h>
#include <stdlib.h>

#define POPULATION 10
#define MATRIX_SIZE_X 5
#define MATRIX_SIZE_Y 5

typedef enum {
    EMPTY,
    SUSCEPTIBLE,
    INFECTED,
    RECOVERED
} State;

typedef struct {
    int x;
    int y;
} Position;

void printMatrix();

void setupSimulation();

void resetMatrix();

Position getRandomEmptyPosition();

void spawnAgents();

State matrix[MATRIX_SIZE_X][MATRIX_SIZE_Y];
Position agentPositions[POPULATION];

int main(){
    setupSimulation();
    return EXIT_SUCCESS;
}

void setupSimulation(){
    //Check if we are all idiots
    if(POPULATION > MATRIX_SIZE_X*MATRIX_SIZE_Y){
        printf("Population is above total number of elements in the matrix.\n");
        exit(EXIT_FAILURE);
    }
    resetMatrix();
    spawnAgents();
    printMatrix();
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

void printMatrix(){
    for(int y=0;y<MATRIX_SIZE_Y;y++){
        if(y==0){
            printf("|");
        } else{
            printf("\n|");
        }
        for(int x=0;x<MATRIX_SIZE_X;x++){
            State state = matrix[x][y];
            switch (state)
            {
            case EMPTY:
                printf(" |");
                break;
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
}