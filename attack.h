#include "variables.h"
#include "main-struct.h"
int Swforcheck[9]={0};


int Check_for_attack(char world[][20],struct sanimal animal,int *p,int *x2,int *y2){
    int k = 0;
    for(int i = animal.x -1 ; i<animal.x +2 ; i++){
        for(int j = animal.y-1 ; j <animal.y +2 ; j++){
            if(Swforcheck[k]==0 && world[i][j] != animal.gender &&  world[i][j] != 'H' && world[i][j] != 'F' && world[i][j] != '-' && world[i][j] != '#' && !(animal.x==i && animal.y==j) && i>=0 && j>=0){
                Swforcheck[k] = 1;
                *p += 1;
                *x2 = i;
                *y2 = j;
                return 1;
            }
            else{
                Swforcheck[k] = 1;
                *p += 1;
            }
            k++;
        } 
    }
    return 0;

}



int attack(struct sanimal *animal, FILE *log){
    int number_dir = 1;
    int x , y;
    int num;
    for(int i = 0 ; i<8 ; i++){
        Swforcheck[i] = 0;
    }

    while(number_dir <= 8){
        if(Check_for_attack(world , *animal , &number_dir ,&x , &y) == 1){
            if(list[serach_for_animal(list , x , y)].defense < animal->attacke ){
                if(list[serach_for_animal(list , x ,y)].energy >  3 *animal->movemente){
                    animal->energy += list[serach_for_animal(list , x ,y)].energy;
                    list[serach_for_animal(list , x ,y)].energy = 0;
                    world[list[serach_for_animal(list , x ,y)].x][list[serach_for_animal(list , x ,y)].y] = '-';
                    printf("attacked to (%d , %d)" , list[serach_for_animal(list , x ,y)].x , list[serach_for_animal(list , x ,y)].y);
                    fprintf(log , "Fight : (%d,%d) with (%d,%d) , winner : %c\n" , animal->x ,animal->y , list[serach_for_animal(list , x ,y)].x , list[serach_for_animal(list , x ,y)].y , animal->gender);
                    return 1;
                }
            }
        }
    
    }
    return -1;


}
