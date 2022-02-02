
#ifndef STRUCT.H 
#define STRUCT.H 

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include"variables.h"




struct initial_energy{
    char gender;
    int energy;
}initialE[10];

struct sanimal{
    int x;
    int y;
    char gender;
    int energy; 
    int movemente;  //movement energy 
    int numberm;   //number of movement
    int productione;  
    int attacke;   
    int defense;

}list[100]; //it is supposed that number of maximum creatures is 10


int search_for_initialE(char gender){
    for(int i = 0 ; i< 10 ; i++){
        if(initialE[i].gender == gender) return initialE[i].energy;
    }
}



int serach_for_animal(struct sanimal list[] , int x , int y){
    for(int i = 0 ; i<number_of_all ; i++){
        if(list[i].x == x && list[i].y ==y){
            return i;
        }
    }
    return -1;
}

#endif 