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
    //Indsæt kode her der sætter alle elementer i matricen til EMPTY
}

Position getRandomEmptyPosition(){
    /*Indsæt kode her der finder og retunere en tilfældig TOM position i matricen,
    ved brug af den Struct der hedder Position. (Keyword TOM).*/
}

void spawnAgents(){
    /*Indsæt kode her der vælger tilfældige pladser i matricen fra getRandomEmptyPosition
    og sætter dem lig med SUSCEPTIBLE, og gemmer denne position i det array der hedder agentPositions.
    Den første agent burde være INFECTED.*/
}

void printMatrix(){
    //Indsæt kode her der printer matricen ved brug af printf.
}