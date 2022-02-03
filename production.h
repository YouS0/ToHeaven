
#ifndef PRODUCTION.H 
#define PRODUCTION.H 

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "variables.h"
#include "main-struct.h"
#include "map-funcs.h"
int Swforproduct[9]={0};


int randint(int lower , int upper){
    srand(time(0));
    return (rand() % (upper - lower + 1)) + lower;
}



void generate_chile(struct sanimal *animal){
    animal->attacke = randint(20 , 500);
    animal->defense = randint(20 , 500);
    animal->movemente = randint(20 , 200);
    animal->numberm = randint(1 , 3);
    animal->productione = randint(60 , 600);
}






int Check_Product(char world[][20],struct sanimal animal,int *p,int *x2,int *y2){
    int k = 0;
    for(int i = animal.x -1 ; i<animal.x +2 ; i++){
        for(int j = animal.y-1 ; j <animal.y +2 ; j++){
            if(Swforproduct[k]==0 && world[i][j] == animal.gender && !(animal.x==i && animal.y==j)){
                Swforproduct[k] = 1;
                *p += 1;
                *x2 = i;
                *y2 = j;
                return 1;
            }
            else{
                Swforproduct[k] = 1;
                *p += 1;
            }
            k++;
        } 
    }
    return 0;

}




int production(struct sanimal *animal , FILE *log){
    int number_dir = 1;
    int x , y;
    int num;
    for(int i = 0 ; i<8 ; i++){
        Swforproduct[i] = 0;
    }
    while(number_dir <= 8){
        if(Check_Product(world , *animal , &number_dir ,&x , &y  ) == 1){
            if(list[serach_for_animal(list , x , y)].energy >= list[serach_for_animal(list , x , y)].productione){
                num = randint(0,1);
                if(num == 1){
                    printf("reproduction . . . ");
                    sleep(1000);
                    animal->energy -= animal->productione/2;
                    list[serach_for_animal(list , x , y)].energy -= list[serach_for_animal(list , x , y)].productione;
                    struct sanimal child;
                    child.gender = animal->gender;
                    theNearest(animal->x , animal->y , '-');
                    world[nearest[0]][nearest[1]] = animal->gender;
                    child.x = nearest[0];
                    child.y = nearest[1];
                    child.energy = search_for_initialE(animal->gender);
                    generate_chile(&child);
                    fprintf(log , "Reproduction : (%d,%d) with (%d,%d) in (%d,%d)\n" , animal->x , animal->y , list[serach_for_animal(list , x , y)].x , list[serach_for_animal(list , x , y)].y , child.x , child.y);
                    number_of_all ++;
                    list[number_of_all - 1] = child; 
                    return 1;

                }
            }
        }
    }
    return 0;
}



#endif 






