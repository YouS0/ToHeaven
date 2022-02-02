#ifndef MAP.H 
#define MAP.H 

#include "variables.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}


void theNearest(int x , int y, char type) {
    int min = 400;
    int distance , dx , dy;
    //--- find the nearest
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (world[i][j] == type) {
                dx = x > i ? x - i : i - x;
                dy = y > j ? y - j : j - y;
                if(dx+dy<min) {
                    min = dx + dy;
                    nearest[0] = i;
                    nearest[1] = j;
                }
            }
        }
    }
    
}

#endif 