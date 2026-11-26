#ifndef AGENTS_C
#define AGENTS_C
#include "agents.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void moveAgent(Agent* agent, int* matrix){
    //collects the current position of the agent
    Position selectedPosition = {agent->position.x, agent->position.y};
    int selectedMovementRating = 0;

    //finds the difference between the agent's current position and the target position
    int diffX = agent->target.x - agent->position.x;
    int diffY = agent->target.y - agent->position.y;
    Position targetDiff = {diffX, diffY};
    Position targetDirection = {0, 0};

    // Calculate target direction
    if (targetDiff.x > 0) {
        targetDirection.x = 1;
    } else if (targetDiff.x < 0) {
        targetDirection.x = -1;
    }

    if (targetDiff.y > 0) {
        targetDirection.y = 1;
    } else if (targetDiff.y < 0) {
        targetDirection.y = -1;
    }


    // Iterates the agents eight neighboring positions
    Position neighborDirection;
    for(neighborDirection.x = -1; neighborDirection.x <= 1; neighborDirection.x++){
        for(neighborDirection.y = -1; neighborDirection.y <= 1; neighborDirection.y++){

            // Finds neighbor position
            Position neighborPosition = {
                agent->position.x + neighborDirection.x,
                agent->position.y + neighborDirection.y
            };

            // Skip positions outside the matrix and occupied positions
            if(neighborPosition.x < 0 || neighborPosition.x >= MATRIX_SIZE_X){
                continue;
            }
            if(neighborPosition.y < 0 || neighborPosition.y >= MATRIX_SIZE_Y){
                continue;
            }
            if(getMatrixValue(neighborPosition, matrix) != EMPTY){
                continue;
            }

            //checks if the currently iterated position would move the agent in the right direction
            //then increases the rating if it does
            int movementRating = 0;

            if(targetDirection.x == neighborDirection.x){
                movementRating += 1;
            }
            if(targetDirection.y == neighborDirection.y){
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
    // if the final selected position is the position the agent is currently standing in
    // then skip the following lines
    if(compareTwoPositions(selectedPosition, agent->position)){
        return;
    }
    // Updates the agent position in the matrix
    int agentIndex = getMatrixValue(agent->position, matrix);
    setMatrixValue(selectedPosition, agentIndex, matrix);
    setMatrixValue(agent->position, EMPTY, matrix);
    // Updates the agents position
    agent->position = selectedPosition;
    switchTarget(agent);
}

void moveAgents(int* matrix, Agent* agents){
    //iterates through the entire given Agent array for the moveAgent function
    for(int index=0;index<POPULATION;index++){
        moveAgent(&agents[index], matrix);
    }
}

void spawnAgents(int* matrix, Agent* agents){
    // creates agents until the amount equals the Population cap
    for(int index=0;index<POPULATION;index++){
        // finds a random empty position and instantiates a new agent
        Position randomPosition = getRandomEmptyPosition(matrix);
        Agent agent;

        // start postion
        agent.position = randomPosition;
        agent.hub1 = agent.position;

        // andet punkt agenten går i mod
        agent.hub2 = getRandomPosition();
        agent.target = agent.hub2;
        setMatrixValue(randomPosition, index, matrix);

        // if the agent is the first one created, then it becomes infected as Patient 0
        if(index == 0){
            agent.state = INFECTED;
            agent.infectionTime = 0;
        } else{
            agent.state = SUSCEPTIBLE;
            agent.infectionTime = -1;
        }

        // finally places the agent into the Agent array for later use
        agents[index] = agent;
    }
}

void switchTarget(Agent* agent) {
    //checks if the Agent has reached it's target
    if (compareTwoPositions(agent->position, agent->target)) {
        //if it has, then make the currently unused 'hub' into it's new target position
        if (compareTwoPositions(agent->target, agent->hub2)) {
            agent->target = agent->hub1;
        } else if (compareTwoPositions(agent->target, agent->hub1)) {
            agent->target = agent->hub2;
        }
    }
}



int compareTwoPositions(Position position1, Position position2) {
    // if the position is the same, returns true, and false if not
    if (position1.x != position2.x || position1.y != position2.y) {
        return False;
    }  return True;
}

void runRecovery(Agent* agents, int currentTime){
    // iterates through the entire Agent array
    for(int agentIndex=0;agentIndex<POPULATION;agentIndex++){
        // checks if the selected agent has been infected longer or equal to the infection duration
        Agent* agent = &agents[agentIndex];
        if (agent->state == INFECTED && currentTime - agent->infectionTime >= INFECTION_DURATION) {
            // if they've gone past the infection duration, they become recovered
            agent->state = RECOVERED;
        }
    }
}


void runTransmissions(int* matrix, Agent* agents, int currentTime){
    //iterates through the entire Agent array
    for(int agentIndex=0;agentIndex<POPULATION;agentIndex++){
        Agent* agent = &agents[agentIndex];
        //checks if the agent is susceptible
        if(agent->state == SUSCEPTIBLE){
            int infectedMaskCount = 0;
            int infectedNoMaskCount = 0;
            getInfectedNeighborCount(agent, matrix, agents, currentTime, &infectedMaskCount, &infectedNoMaskCount);
            agent->state = getInfection(infectedMaskCount, infectedNoMaskCount);
            // if the Agent becomes infected, assign the current time as the infection time
            if(agent->state == INFECTED) {
                agent->infectionTime = currentTime;
            }
        }
    }
}

void getInfectedNeighborCount(const Agent* agent, int* matrix, Agent* agents, int currentTime, int* infectedMaskCount, int* infectedNoMaskCount){


    *infectedMaskCount = 0;
    *infectedNoMaskCount = 0;
    //iterates through the 8 surrounding tiles
    for(int x=-1;x<=1;x++){
        for(int y=-1;y<=1;y++){
            // the following if statements check if the currently selected tile is:
            // the tile of the selected agent
            if(x == 0 && y == 0){
                continue;
            }
            // outside the bounds of the matrix
            Position neighborPosition = {agent->position.x+x, agent->position.y+y};
            if(neighborPosition.x < 0 || neighborPosition.x >= MATRIX_SIZE_X){
                continue;
            }
            if(neighborPosition.y < 0 || neighborPosition.y >= MATRIX_SIZE_Y){
                continue;
            }
            // or empty
            if(getMatrixValue(neighborPosition, matrix) == EMPTY){
                continue;
            }
            // if the tile contains an agent, check if they are infected and tally the counter accordingly
            Agent* neighbor = &agents[getMatrixValue(neighborPosition, matrix)];
            if(neighbor->state == INFECTED && neighbor->infectionTime != currentTime){
                if (neighbor->wearsMask) {
                    (*infectedMaskCount)++;
                } else{
                    (*infectedNoMaskCount)++;
                }

            }
        }
    }
}

State getInfection(int infectedMaskCount, int infectedNoMaskCount ){
    // converts TRANSMISSION_RISK_PERCENT to a probability between 0-1

    double pWearsMask = TRANSMISSION_RISK_MASK_PERCENT/100.0;
    double pWearsNoMask = TRANSMISSION_RISK_PERCENT/100.0;

    // calculates the risk of at least one of the infected neighbors transmits the infection
    double riskOfInfection = 1-pow(1.0-pWearsNoMask,infectedNoMaskCount)*pow(1.0-pWearsMask,infectedMaskCount);
    double randomNumber = rand() /(double)RAND_MAX;
    //if the random number (between 0 and 1) is lower than risk of infection, return infected
    if(randomNumber < riskOfInfection){
        return INFECTED;
    }
    else{
        return SUSCEPTIBLE;
    }
}

#endif
