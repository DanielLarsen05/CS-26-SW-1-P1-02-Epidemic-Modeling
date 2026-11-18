#ifndef AGENTS_C
#define AGENTS_C
#include "agents.h"
#include "matrix.h"
#include <stdlib.h>

void moveAgent(Agent agent){
    Position selectedPosition = {agent.position.x-1, agent.position.y-1};
    int selectedRating = 0;
    for(int x=-1;x<=1;x++){
        for(int y=-1;y<=1;y++){
            if(matrix[x][y] != EMPTY){
                continue;
            } 
            if(x == 0 && y == 0){
                continue;
            }
            Position neighborPosition = {agent.position.x+x, agent.position.y+y};
            if(neighborPosition.x < 0 || neighborPosition.x >= MATRIX_SIZE_X){
                continue;
            }
            if(neighborPosition.y < 0 || neighborPosition.y >= MATRIX_SIZE_Y){
                continue;
            }
            int diffX = agent.target.x - agent.position.x;
            int diffY = agent.target.y - agent.position.y;
            int directionX = 0;
            int directionY = 0;
            if(diffX > 0){
                directionX = diffX/diffX;
            }
            if(diffY > 0){
                directionY = diffY/diffY;
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
    matrix[selectedPosition.x][selectedPosition.y] = matrix[agent.position.x][agent.position.y];
    matrix[agent.position.x][agent.position.y] = EMPTY;
    agent.position = selectedPosition;
}

void moveAgents(){
    for(int index=0;index<POPULATION;index++){
        moveAgent(agents[index]);
    }
}

void spawnAgents(){
    for(int index=0;index<POPULATION;index++){
        Position randomPosition = getRandomEmptyPosition();
        Agent agent;
        // start postion
        agent.position = randomPosition;
        agent.hub1=agent.position;
        // andet punkt agenten går i mod
        agent.hub2=getRandomEmptyPosition();
        agent.target = agent.hub2;
        matrix[randomPosition.x][randomPosition.y] = index;
        if(index == 0){
            agent.state = INFECTED;
        } else{
            agent.state = SUSCEPTIBLE;
        }
        agents[index] = agent;
    }
}

void switchTarget(Agent agent) {
    if (agent.position == agent.target) {
        if (agent.target == agent.hub2) {
            agent.target = agent.hub1;
        } else if (agent.target == agent.hub1) {
            agent.target = agent.hub2;
        } else {
            return;
        }
    }
}



void runTransmisssions(){
    for(int agentIndex=0;agentIndex<POPULATION;agentIndex++){
        Agent agent = agents[agentIndex];
        if(agent.state == SUSCEPTIBLE){
            int infectedNeighborCount = getInfectedNeighborCount(agent);
            agent.state = getInfection(infectedNeighborCount);
        }
    }
}

int getInfectedNeighborCount(Agent agent){
    int infectedCount = 0;
    for(int x=-1;x<=1;x++){
        for(int y=-1;y<=1;y++){
            if(matrix[x][y] != EMPTY){
                continue;
            }
            if(x == 0 && y == 0){
                continue;
            }
            Position neighborPosition = {agent.position.x+x, agent.position.y+y};
            if(neighborPosition.x < 0 || neighborPosition.x >= MATRIX_SIZE_X){
                continue;
            }
            if(neighborPosition.y < 0 || neighborPosition.y >= MATRIX_SIZE_Y){
                continue;
            }
            Agent neighbor = agents[matrix[neighborPosition.x][neighborPosition.y]];
            if(neighbor.state == INFECTED){
                infectedCount += 1;
            }
        }
    }
    return infectedCount;
}

State getInfection(int infectedCount){
    double chanceOfInfection = TRANSMISSION_RATE*infectedCount/8.0;
    double randomNumber = (double) rand() / RAND_MAX;
    if(randomNumber < chanceOfInfection){
        return INFECTED;
    }
    else{
        return SUSCEPTIBLE;
    }
}

#endif