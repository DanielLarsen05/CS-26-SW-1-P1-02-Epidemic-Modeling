#ifndef AGENTS_C
#define AGENTS_C
#include "agents.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void moveAgent(Agent* agent){
    Position selectedPosition = {agent->position.x, agent->position.y};
    int selectedMovementRating = 0;


    int diffX = agent->target.x - agent->position.x;
    int diffY = agent->target.y - agent->position.y;
    int targetDirectionX = 0;
    int targetDirectionY = 0;

    // Calculate target direction
    if (diffX > 0) {
        targetDirectionX = 1;
    } else if (diffX < 0) {
        targetDirectionX = -1;
    }

    if (diffY > 0) {
        targetDirectionY = 1;
    } else if (diffY < 0) {
        targetDirectionY = -1;
    }


    // Iterates the agents eight neighboring positions
    for(int neighborDirectionX = -1; neighborDirectionX <= 1; neighborDirectionX++){
        for(int neighborDirectionY = -1; neighborDirectionY <= 1; neighborDirectionY++){

            // Finds neighbor position
            Position neighborPosition = {
                agent->position.x + neighborDirectionX,
                agent->position.y + neighborDirectionY
            };

            // Skip positions outside the matrix
            if(neighborPosition.x < 0 || neighborPosition.x >= MATRIX_SIZE_X){
                continue;
            }
            if(neighborPosition.y < 0 || neighborPosition.y >= MATRIX_SIZE_Y){
                continue;
            }

            // Skip positions occupied by other agents
            if(matrix[neighborPosition.x][neighborPosition.y] != EMPTY){
                continue;
            }


            int movementRating = 0;

            if(targetDirectionX == neighborDirectionX){
                movementRating += 1;
            }
            if(targetDirectionY == neighborDirectionY){
                movementRating += 1;
            }

            // Selects the position with the highest movement rating
            if(movementRating > selectedMovementRating){
                selectedPosition.x = neighborPosition.x;
                selectedPosition.y = neighborPosition.y;
                selectedMovementRating = movementRating;
            }
        }

    }

    // Updates the agent position in the matrix
    if (selectedPosition.x != agent->position.x || selectedPosition.y != agent->position.y) {
        matrix[selectedPosition.x][selectedPosition.y] = matrix[agent->position.x][agent->position.y];
        matrix[agent->position.x][agent->position.y] = EMPTY;

        // Updates the agents position
        agent->position = selectedPosition;

        switchTarget(agent);
    }

}

void moveAgents(){
    for(int index=0;index<POPULATION;index++){
        moveAgent(&agents[index]);
    }
}

void spawnAgents(){
    for(int index=0;index<POPULATION;index++){
        Position randomPosition = getRandomEmptyPosition();
        Agent agent;
        // start postion
        agent.position = randomPosition;
        agent.hub1 = agent.position;
        // andet punkt agenten går i mod
        agent.hub2 = getRandomPosition();
        agent.target = agent.hub2;
        matrix[randomPosition.x][randomPosition.y] = index;
        if(index == 0){
            agent.state = INFECTED;
            agent.infectionTime = 0;
        } else{
            agent.state = SUSCEPTIBLE;
            agent.infectionTime = -1;
        }
        agents[index] = agent;
    }
}

void switchTarget(Agent* agent) {
    if (compareTwoPositions(agent->position, agent->target)) {
        if (compareTwoPositions(agent->target, agent->hub2)) {
            agent->target = agent->hub1;
        } else if (compareTwoPositions(agent->target, agent->hub1)) {
            agent->target = agent->hub2;
        }
    }
}



int compareTwoPositions(Position position1, Position position2) {
    if (position1.x != position2.x || position1.y != position2.y) {
        return 0;
    }  return 1;
}

void runRecovery(){
    for(int agentIndex=0;agentIndex<POPULATION;agentIndex++){
        Agent* agent = &agents[agentIndex];
        if (agent->state == INFECTED && currentTime - agent->infectionTime >= INFECTION_DURATION) {
            agent->state = RECOVERED;
        }
    }
}


void runTransmissions(){
    for(int agentIndex=0;agentIndex<POPULATION;agentIndex++){
        Agent* agent = &agents[agentIndex];
        if(agent->state == SUSCEPTIBLE){
            int infectedNeighborCount = getInfectedNeighborCount(agent);
            agent->state = getInfection(infectedNeighborCount);
            if(agent->state == INFECTED) {
                agent->infectionTime = currentTime;
            }
        }
    }
}

int getInfectedNeighborCount(const Agent* agent){
    int infectedCount = 0;
    for(int x=-1;x<=1;x++){
        for(int y=-1;y<=1;y++){
            if(x == 0 && y == 0){
                continue;
            }
            Position neighborPosition = {agent->position.x+x, agent->position.y+y};
            if(neighborPosition.x < 0 || neighborPosition.x >= MATRIX_SIZE_X){
                continue;
            }
            if(neighborPosition.y < 0 || neighborPosition.y >= MATRIX_SIZE_Y){
                continue;
            }
            if(matrix[neighborPosition.x][neighborPosition.y] == EMPTY){
                continue;
            }
            Agent* neighbor = &agents[matrix[neighborPosition.x][neighborPosition.y]];
            if(neighbor->state == INFECTED && neighbor->infectionTime != currentTime){
                infectedCount += 1;
            }
        }
    }
    return infectedCount;
}

State getInfection(int infectedCount){
    int riskOfInfection = TRANSMISSION_RISK_PERCENT*infectedCount;
    int randomNumber = rand() % 100;
    if(randomNumber < riskOfInfection){
        return INFECTED;
    }
    else{
        return SUSCEPTIBLE;
    }
}

#endif
