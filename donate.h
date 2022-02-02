#ifndef DONATE_H
#define DONATE_H
#include "variables.h"
#include "main-struct.h"


int search_for_donate(struct sanimal list[] , struct sanimal animal){
    int min;
    int position;
    for(int i = 0 ; i<number_of_all ; i++){
        if(list[i].gender == animal.gender && list[i].energy < list[i].movemente) {
            position = i;
            return position;
        }
        return -1;
    }


}

int donate(struct sanimal *animal){
    int position = search_for_donate(list , *animal);
    if(position != -1){
        animal->energy -= animal->movemente;
        list[position].energy += animal->movemente;
        printf("Donated to (%d,%d)" , list[position].x , list[position].y);
        return 1;
    }
    return -1;



}








#endif