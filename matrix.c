#ifndef MATRIX_H
#define MATRIX_H
#include "defines.h"
#include <stdio.h>

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

#endif