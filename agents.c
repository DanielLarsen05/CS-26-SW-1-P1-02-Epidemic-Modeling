#ifndef AGENTS_C
#define AGENTS_C
#include "agents.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void moveAgent(Agent* agent, int* matrix){
    //collects the current position of the agent
    Position selectedPosition = {agent->position.x, agent->position.y};
    int selectedMovementRating = 0;

    //finds the difference between the agent's current position and the target position
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
            if(getMatrixValue(neighborPosition, matrix) != EMPTY){
                continue;
            }

            //checks if the currently iterated position would move the agent in the right direction
            //then increases the rating if it does
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
        return 0;
    }  return 1;
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
            // finds all neighbors and randomly decides if the Agent gets infected
            // weighted by the amount of infected neighbors
            int infectedNeighborCount = getInfectedNeighborCount(agent, matrix, agents, currentTime);
            agent->state = getInfection(infectedNeighborCount);
            // if the Agent becomes infected, assign the current time as the infection time
            if(agent->state == INFECTED) {
                agent->infectionTime = currentTime;
            }
        }
    }
}

int getInfectedNeighborCount(const Agent* agent, int* matrix, Agent* agents, int currentTime){
    int infectedCount = 0;
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
                infectedCount += 1;
            }
        }
    }
    // returns the final amount of infected neighbors
    return infectedCount;
}

State getInfection(int infectedCount){
    // calculates the risk of infection based on the infected count
    int riskOfInfection = TRANSMISSION_RISK_PERCENT*infectedCount;
    int randomNumber = rand() % 100;
    //if the random number (between 0 and 99) if lower than risk of infection, return infected
    if(randomNumber < riskOfInfection){
        return INFECTED;
    }
    else{
        return SUSCEPTIBLE;
    }
}

#endif
