#ifndef AGENTS_C
#define AGENTS_C
#include "agents.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void moveAgent(Agent* agent, int* matrix){
    Position selectedPosition = {agent->position.x, agent->position.y};
    int selectedRating = 0;
    for(int x=-1;x<=1;x++){
        for(int y=-1;y<=1;y++){
            Position neighborPosition = {agent->position.x+x, agent->position.y+y};
            if(neighborPosition.x < 0 || neighborPosition.x >= MATRIX_SIZE_X){
                continue;
            }
            if(neighborPosition.y < 0 || neighborPosition.y >= MATRIX_SIZE_Y){
                continue;
            }
            if(getMatrixValue(neighborPosition, matrix) != EMPTY){
                continue;
            }
            int diffX = agent->target.x - agent->position.x;
            int diffY = agent->target.y - agent->position.y;
            int directionX = 0;
            int directionY = 0;
            if(diffX != 0){
                directionX = abs(diffX)/diffX;
            }
            if(diffY != 0){
                directionY = abs(diffY)/diffY;
            }
            int rating = 0;
            if(directionX == x){
                rating += 1;
            }
            if(directionY == y){
                rating += 1;
            }
            if(rating > selectedRating){
                selectedPosition.x = neighborPosition.x;
                selectedPosition.y = neighborPosition.y;
                selectedRating = rating;
            }
        }
    }
    if(compareTwoPositions(selectedPosition, agent->position)){
        return;
    }
    int agentIndex = getMatrixValue(agent->position, matrix);
    setMatrixValue(selectedPosition, agentIndex, matrix);
    setMatrixValue(agent->position, EMPTY, matrix);
    agent->position = selectedPosition;
    switchTarget(agent);
}

void moveAgents(int* matrix, Agent* agents){
    for(int index=0;index<POPULATION;index++){
        moveAgent(&agents[index], matrix);
    }
}

void spawnAgents(int* matrix, Agent* agents){
    for(int index=0;index<POPULATION;index++){
        Position randomPosition = getRandomEmptyPosition(matrix);
        Agent agent;
        // start postion
        agent.position = randomPosition;
        agent.hub1 = agent.position;
        // andet punkt agenten går i mod
        agent.hub2 = getRandomPosition();
        agent.target = agent.hub2;
        setMatrixValue(randomPosition, index, matrix);
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

void runRecovery(Agent* agents, int currentTime){
    for(int agentIndex=0;agentIndex<POPULATION;agentIndex++){
        Agent* agent = &agents[agentIndex];
        if (agent->state == INFECTED && currentTime - agent->infectionTime >= INFECTION_DURATION) {
            agent->state = RECOVERED;
        }
    }
}


void runTransmissions(int* matrix, Agent* agents, int currentTime){
    for(int agentIndex=0;agentIndex<POPULATION;agentIndex++){
        Agent* agent = &agents[agentIndex];
        if(agent->state == SUSCEPTIBLE){
            int infectedNeighborCount = getInfectedNeighborCount(agent, matrix, agents, currentTime);
            agent->state = getInfection(infectedNeighborCount);
            if(agent->state == INFECTED) {
                agent->infectionTime = currentTime;
            }
        }
    }
}

int getInfectedNeighborCount(const Agent* agent, int* matrix, Agent* agents, int currentTime){
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
            if(getMatrixValue(neighborPosition, matrix) == EMPTY){
                continue;
            }
            Agent* neighbor = &agents[getMatrixValue(neighborPosition, matrix)];
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
