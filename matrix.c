#ifndef MATRIX_C
#define MATRIX_C
#include "defines.h"
#include "agents.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void printMatrixIndex(int* matrix, int currentTime){
    if(!VISUAL_MODE){
        return;
    }
    // first it writes the current timestep of the simulation
    printf("Time: %d\n", currentTime);
    // then it creates a for loop to iterate through the y axis
    for(int y=0;y<MATRIX_SIZE_Y;y++){
        // if it's the first line, it just makes a |, while on other layers it creates a newline before doing so
        if(y==0){
            printf("|");
        } else{
            printf("\n|");
        }
        // after creating the | write out the index number state in the cell, or nothing if empty,
        // followed by another |  (reread later to correct if it's wrong)
        for(int x=0;x<MATRIX_SIZE_X;x++){
            Position currentPosition = {x, y};
            int agentIndex = getMatrixValue(currentPosition, matrix);
            printf("%2d|", agentIndex);
        }
    }
    // creates 2 newlines so there's a gap for the next thing to be printed
    printf("\n\n");
}

void printMatrix(int* matrix, Agent* agents, int currentTime){
    if(VISUAL_MODE == 0){
        return;
    }
    //prints the current time
    printf("Time: %d\n", currentTime);
    // iterates through the y layer of the matrix
    for(int y=0;y<MATRIX_SIZE_Y;y++){
        // if it's the first line, it just makes a |, while on other layers it creates a newline before doing so
        if(y==0){
            printf("|");
        } else{
            printf("\n|");
        }
        //iterates through the x layer of the matrix
        for(int x=0;x<MATRIX_SIZE_X;x++){
            // gets the current position and checks if there is an agent present,
            // if not, it prints an empty 'square' and moves on the the next placement
            Position currentPosition = {x, y};
            int agentIndex = getMatrixValue(currentPosition, matrix);
            if(agentIndex == EMPTY){
                printf(" |");
                continue;
            }

            // if an agent was grabbed from the position, it prints the state of the agent in the 'square'
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
    // a double newline is made to make a gap for future printing
    printf("\n\n");
}

void resetMatrix(int* matrix){
    //run through all the spaces in the matrix and set them to empty
    for(int x=0;x<MATRIX_SIZE_X;x++){
        for(int y=0;y<MATRIX_SIZE_Y;y++){
            Position currentPosition = {x, y};
            setMatrixValue(currentPosition, EMPTY, matrix);
        }
    }
}

Position getRandomPosition(){
    // this gets 2 random valuers, one corresponding to x, the other y.
    // they are limited to be within the matrix and are returned as a 'position' struct
    int randomX = rand() % MATRIX_SIZE_X;
    int randomY = rand() % MATRIX_SIZE_Y;
    Position randomPosition = {randomX, randomY};
    return randomPosition;
}

Position getRandomEmptyPosition(int* matrix){
    // takes a random position and checks if it is empty,
    // if it is not empty, it will continue taking a new position until it gets an empty position
    Position randomPosition = getRandomPosition();
    while(getMatrixValue(randomPosition, matrix) != EMPTY){
        randomPosition = getRandomPosition();
    }
    return randomPosition;
}

int getMatrixValue(Position position, int* matrix){
    // it grabs the value in the matrix of given position, and returns it as an int
    return matrix[position.x+MATRIX_SIZE_X*position.y];
}

void setMatrixValue(Position position, int value, int* matrix){
    // replaces a value at the given position in the matrix with a given value
    matrix[position.x+MATRIX_SIZE_X*position.y] = value;
}

int getInfectedCount(Agent* agents){
    // initializes a counter, and then checks every agent in the Agent array if they are infected
    int infectedCount=0;
    for (int agentIndex=0; agentIndex<POPULATION; agentIndex++) {
        // if the currently measured agent is infected, it increases the counter by 1
        if (agents[agentIndex].state == INFECTED){
            infectedCount++;
        }
    }
    // and then it returns the number of infected found in the agent array
    return infectedCount;
}

int getSusceptibleCount(Agent* agents){
    // initializes a counter, and then checks every agent in the Agent array if they are susceptible
    int susceptibleCount=0;
    for (int agentIndex=0; agentIndex<POPULATION; agentIndex++) {
        // if the currently measured agent is susceptible, it increases the counter by 1
        if (agents[agentIndex].state == SUSCEPTIBLE){
            susceptibleCount++;
        }
    }
    // and then it returns the number of infected found in the agent array
    return susceptibleCount;
}

int getRecoveredCount(Agent* agents){
    // initializes a counter, and then checks every agent in the Agent array if they are Recovered
    int recoveredCount=0;
    for (int agentIndex=0; agentIndex<POPULATION; agentIndex++) {
        // if the currently measured agent is recovered, it increases the counter by 1
        if (agents[agentIndex].state == RECOVERED){
            recoveredCount++;
        }
    }
    // and then it returns the number of recovered found in the agent array
    return recoveredCount;
}

#endif