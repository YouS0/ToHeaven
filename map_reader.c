#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "main-struct.h"
#include "map-funcs.h"
#include "production.h"
#include "variables.h"
#include "attack.h"
#include "donate.h"
//#include "move.h"
void setTextColor(int textColor, int backColor) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle, colorAttribute);

}
int SearchFood(int i,int j){
    for(int k=0;k<NumberFood*2;k+=2){
        if(Food_Position[k]==i && Food_Position[k+1]==j) return k;
    }
    return -1;
}


void clearScreen() {
    system("clear");
}




void mapprinter(char world[][20],int size ,struct sanimal animal){
    printf("\n");
    int x = animal.x;
    int y = animal.y;
    for(int i=0;i<size;i++){
        printf("|");
        for(int j=0;j<size;j++){
            if(x==i && y==j && animal.energy>0){
                setTextColor(4,0);
            }
            printf("%c",world[i][j]);
            setTextColor(11,0);
            printf("|");
        }
        printf("\n");
    }
    printf("\n");
}

void swap(char world[][20],int a,int b,int i,int j){
    char temp;
    temp=world[a][b];
    world[a][b]=world[i][j];
    world[i][j]=temp;
}

int movethiky(struct sanimal *animal,char direction , int number_of_direction){
    int x=animal->x;
    int y=animal->y;
    if(direction=='a'){
        for(int i = 1 ; i <= number_of_direction ; i++){
            if(world[x][y-i] == 'H') sw = 1;
            if (world[x][y-i] != 'H' && world[x][y-i] != 'F' && world[x][y-i] != '-'){
                return -1;
            }
        }
        for(int i = 1 ; i<= number_of_direction ; i++){
            if(world[x][y-i]=='F') {
                animal->energy += Food_energy[SearchFood(x,y-i)];
                Food_energy[SearchFood(x,y-i)] = 0;
                world[x][y-i] = '-';
            }
        }
        
        if( sw != 1){
            swap(world,x,y,x,y-number_of_direction);
            animal->y-=number_of_direction;
        }
    }

    else if(direction=='w'){
        for(int i = 1 ; i <= number_of_direction ; i++){
            if(world[x-i][y] == 'H') sw = 1;
            if (world[x-i][y] != 'H' && world[x-i][y] != 'F' && world[x-i][y] != '-'){
                return -1;
            }
        }
        for(int i = 1 ; i<= number_of_direction ; i++){
            if(world[x-i][y]=='F') {
                animal->energy += Food_energy[SearchFood(x-i,y)];
                Food_energy[SearchFood(x-i,y)] = 0;
                world[x-i][y] = '-';
            }
        }
        if( sw != 1){
            swap(world,x,y,x-number_of_direction,y);
            animal->x-=number_of_direction;
        }
    }

    else if(direction=='d'){
        for(int i = 1 ; i <= number_of_direction ; i++){
            if(world[x][y+i] == 'H') sw = 1;
            if (world[x][y+i] != 'H' && world[x][y+i] != 'F' && world[x][y+i] != '-'){
                return -1;
            }
        }
        for(int i = 1 ; i<= number_of_direction ; i++){
            if(world[x][y+i]=='F') {
                animal->energy += Food_energy[SearchFood(x,y+i)];
                Food_energy[SearchFood(x,y+i)] = 0;
                world[x][y+i] = '-';
            }
        }
        if( sw != 1){
            swap(world,x,y,x,y+number_of_direction);
            animal->y+=number_of_direction;
        }
    }

    else if(direction=='x'){
        for(int i = 1 ; i <= number_of_direction ; i++){
            if(world[x+i][y] == 'H') sw = 1;
            if (world[x+i][y] != 'H' && world[x+i][y] != 'F' && world[x+i][y] != '-'){
                return -1;
            
            }
        }
        for(int i = 1 ; i<= number_of_direction ; i++){
            if(world[x+i][y]=='F') {
                animal->energy += Food_energy[SearchFood(x+i,y)];
                Food_energy[SearchFood(x+i,y)] = 0;
                world[x+i][y] = '-';
            }
        }
        if( sw != 1){
            swap(world,x,y,x+number_of_direction,y);
            animal->x+=number_of_direction;
        }
    }

    else if(direction=='z'){
        for(int i = 1 ; i <= number_of_direction ; i++){
            if(world[x+i][y-i] == 'H') sw = 1;
            if (world[x+i][y-i] != 'H' && world[x+i][y-i] != 'F' && world[x+i][y-i] != '-'){
                return -1;
            }
        }
        for(int i = 1 ; i<= number_of_direction ; i++){
            if(world[x+i][y-i]=='F') {
                animal->energy += Food_energy[SearchFood(x+i,y-i)];
                Food_energy[SearchFood(x+i,y-i)] = 0;
                world[x+i][y-i] = '-';
            }
        }
        if( sw != 1){
            swap(world,x,y,x+number_of_direction,y-number_of_direction);
            animal->x+=number_of_direction;
            animal->y-=number_of_direction;
        }
    }

    else if(direction=='c'){
        for(int i = 1 ; i <= number_of_direction ; i++){
            if(world[x+i][y+i] == 'H') sw = 1;
            if (world[x+i][y+i] != 'H' && world[x+i][y+i] != 'F' && world[x+i][y+i] != '-'){
                return -1;
            }
        }
        for(int i = 1 ; i<= number_of_direction ; i++){
            if(world[x+i][y+i]=='F') {
                animal->energy += Food_energy[SearchFood(x+i,y+i)];
                Food_energy[SearchFood(x+i,y+i)] = 0;
                world[x+i][y+i] = '-';
            }
        }
        if( sw != 1){
            swap(world,x,y,x+number_of_direction,y+number_of_direction);
            animal->x+=number_of_direction;
            animal->y+=number_of_direction;
        }
    }

    else if(direction=='q'){
        for(int i = 1 ; i <= number_of_direction ; i++){
            if(world[x-i][y-i] == 'H') sw = 1;
            if (world[x-i][y-i] != 'H' && world[x-i][y-i] != 'F' && world[x-i][y-i] != '-'){
                return -1;
            }
        }
        for(int i = 1 ; i<= number_of_direction ; i++){
            if(world[x-i][y-i]=='F') {
                animal->energy += Food_energy[SearchFood(x-i,y-i)];
                Food_energy[SearchFood(x-i,y-i)] = 0;
                world[x-i][y-i] = '-';
            }
        }
        if( sw != 1){
            swap(world,x,y,x-number_of_direction,y-number_of_direction);
            animal->x-=number_of_direction;
            animal->y-=number_of_direction;
        }
    }

    else if(direction=='e'){
        for(int i = 1 ; i <= number_of_direction ; i++){
            if(world[x-i][y+i] == 'H') sw = 1;
            if (world[x-i][y+i] != 'H' && world[x-i][y+i] != 'F' && world[x-i][y+i] != '-'){
                return -1;
            }
        }
        for(int i = 1 ; i<= number_of_direction ; i++){
            if(world[x-i][y+i]=='F') {
                animal->energy += Food_energy[SearchFood(x-i,y+i)];
                Food_energy[SearchFood(x-i,y+i)] = 0;
                world[x-i][y+i] = '-';
            }
        }
        if( sw != 1){
            swap(world,x,y,x-number_of_direction,y+number_of_direction);
            animal->x-=number_of_direction;
            animal->y+=number_of_direction;
        }
    }
    if(sw == 1) winner = animal->gender;

    return 1;
}

int move_all_directions(struct sanimal *animal,char dr1,char dr2,char dr3,char dr4,char dr5,char dr6,char dr7,char dr8){
    int restlt = 0;
    restlt = movethiky(animal , dr1 , 1);
    if (restlt == 1) return 1;
    restlt = movethiky(animal , dr2 , 1);
    if (restlt == 1) return -1;
    restlt = movethiky(animal , dr3 , 1);
    if (restlt == 1) return -1;
    restlt = movethiky(animal , dr4 , 1);
    if (restlt == 1) return -1;
    restlt = movethiky(animal , dr5 , 1);
    if (restlt == 1) return -1;
    restlt = movethiky(animal , dr6 , 1);
    if (restlt == 1) return -1;
    restlt = movethiky(animal , dr7 , 1);
    if (restlt == 1) return -1;
    restlt = movethiky(animal , dr8 , 1);
    if (restlt == 1) return -1;
}


int moveUnc(struct sanimal *animal) {
    int result = 0;
    theNearest(animal->x , animal->y , 'H');
    if(nearest[0]>animal->x){
        if(nearest[1]>animal->y) result = move_all_directions(animal , 'c' , 'd' , 'x' , 'z' , 'e' , 'a' , 'w' , 'q');
        else if(nearest[1]<animal->y) result = move_all_directions(animal , 'z' , 'a' , 'x' , 'c' , 'q' , 'w' , 'd' , 'e');
        else if(nearest[1] == animal->y) result = move_all_directions(animal , 'x' , 'c' , 'z' , 'a' , 'd' , 'w' , 'e' , 'q');
    }
    else if(nearest[0]<animal->x){
        if(nearest[1]>animal->y) result = move_all_directions(animal , 'e' , 'd' , 'w' , 'c' , 'x' , 'a' , 'q' , 'z');
        else if(nearest[1]<animal->y) result = move_all_directions(animal , 'q' , 'w' , 'a' , 'z' , 'x' , 'e' , 'd' , 'c');
        else if(nearest[1] == animal->y) result = move_all_directions(animal , 'w' , 'e' , 'q' , 'a' , 'd' , 'x' , 'c' , 'z');
    }
    else if(nearest[0]== animal->x){
        if(nearest[1]>animal->y) result = move_all_directions(animal , 'd' , 'e' , 'c' , 'x' , 'w' , 'a' , 'q' , 'z');
        else if(nearest[1]<animal->y) result = move_all_directions(animal , 'a' , 'q' , 'z' , 'x' , 'w' , 'd' , 'e' , 'c');
    }
    return result;
}

void mapreader(FILE *readfile){
    char lines[100];
    int heaven_cords[100];
    int deadend_cords[200];
    int creatures_cord[200];
    int heavens;
    int deadends;
    int position;
    fgets(lines , 100 , readfile);
    size = atof(&lines[0]);
    //input size of world
    for(int i = 0 ; i<size ; i++){
        for(int j = 0 ; j<size ; j++){
            world[i][j]='-';
        }
    }

    fgets(lines , 100 , readfile);
    deadends = atof(&lines[2]);
    position = 0;
    for(int i = 5 ; i<strlen(lines) ; i++){
        if(lines[i]>='0' && lines[i]<='9') {
            deadend_cords[position] = atof(&lines[i]);
            position +=1;
            if(atof(&lines[i])>=10)i++;
        }
    }
    //get deadend cordinators
    for(int j = 0 ; j<2*deadends ; j++){
        world[deadend_cords[j]][deadend_cords[j+1]] = '#';
        j++;
    }
    //apply the deadends in final world cordinators
    fgets(lines , 100 , readfile);
    heavens = atof(&lines[2]);
    position = 0;
    for(int i = 5 ; i<strlen(lines) ; i++){
        if(lines[i]>='0' && lines[i]<='9') {
            heaven_cords[position] = atof(&lines[i]);
            position +=1;
            if(atof(&lines[i])>=10)i++;
        }
    }
    //get heaven cordinators
    for(int j = 0 ; j<2*heavens ; j++){
        world[heaven_cords[j]][heaven_cords[j+1]] = 'H';
        j++;
    }
    //apply heaven cordinators to final world
    
    char endofline[]="===\n";
    int k = 0;
    int i=0;
    char ch;
    fscanf(readfile,"%s\n",&endofline);
    fscanf(readfile,"%c",&ch);
    while (ch=='F'){
        fscanf(readfile,"%d ",&Food_energy[k]);
        fscanf(readfile,"%c",&ch);
        fscanf(readfile,"%d",&Food_Position[i]);
        fscanf(readfile,"%c",&ch);
        fscanf(readfile,"%d",&Food_Position[i+1]);
        fscanf(readfile,"%c\n",&ch);
        fscanf(readfile,"%c",&ch);
        k++,i+=2,NumberFood++;
    }
    for(int i = 0 ; i < NumberFood*2; i+=2){
        world[Food_Position[i]][Food_Position[i+1]] = 'F';
    }
    fscanf(readfile,"%c%c\n",&ch,&ch);

    strcpy(endofline,"===\n");
    fgets(lines , 100 ,readfile);
    int numberOfCreatures=0;
    k=0;
    while(strcmp(lines,endofline)!=0){
        numberOfCreatures = atof(&lines[2]);
        number_of_all += numberOfCreatures;
        position = k;
        for(int i = 5 ; i<strlen(lines);i++){
            if(lines[i]>='0' && lines[i]<='9') {
                creatures_cord[position] = atof(&lines[i]);
                position +=1;
                if(atof(&lines[i])>=10)i++;
            }
        }

        for(int j = 0 ; j<numberOfCreatures ; j++){
            list[k/2].gender = lines[0];
            list[k/2].x = creatures_cord[k];
            list[k/2].y = creatures_cord[k+1];
            k += 2;
        }
        fgets(lines , 100 ,readfile);
    }
    controlanimal=fgetc(readfile);
    fgetc(readfile);
    fscanf(readfile,"%s",endofline);
    char gender;
    i=0;
    int index_energy=0;
    while(!feof(readfile)){

        fscanf(readfile," %c",&list[i].gender);
        fscanf(readfile,"%d",&list[i].energy);
        initialE[index_energy].energy = list[i].energy;
        initialE[index_energy].gender = list[i].gender;
        index_energy ++;
        fscanf(readfile,"%d$",&list[i].movemente);
        fscanf(readfile,"%d$",&list[i].numberm);
        fscanf(readfile,"%d$",&list[i].productione);
        fscanf(readfile,"%d$",&list[i].attacke);
        fscanf(readfile,"%d",&list[i].defense);
        int j;
        for(j = i+1 ; list[j].gender == list[i].gender ; j++){
            list[j].energy = list[i].energy;
            list[j].movemente = list[i].movemente;
            list[j].numberm = list[i].numberm;
            list[j].productione = list[i].productione;
            list[j].attacke = list[i].attacke;
            list[j].defense = list[i].defense;
        }
        i = j;
    }   
    for(int i = 0 ; i<number_of_all ; i++){
        world[list[i].x][list[i].y] = list[i].gender; 
    }

}

int main(){

    // FILE *log;
    // log = fopen("game-log.txt" , "wt");
    FILE *readfile;
    int c[2];

    readfile = fopen("C:\\Team_7_Final_Project\\map-phase1.txt" , "rt" );
    //if(!readfile || !log) printf("File did not open!");
    setTextColor(11 , 0);
    mapreader(readfile);
    printf("\n");
    printf("The Creature under your control : %c\n",controlanimal);
    printf("MOVE with:\n");
    printf("          q -- w -- e\n");
    printf("          |    |    |\n");
    printf("          a -- @ -- d\n");
    printf("          |    |    |\n");
    printf("          z -- x -- c\n");
    for(int i = 0 ; i<NumberFood ; i++){
        if(Food_energy[i] != 0) printf("Food In position (%d,%d) has %d\n" , Food_Position[2*i] , Food_Position[2*i+1] , Food_energy[i]);
    }
    int result;
    sw = 0;
    int j;
    char Activity[7];
    int production_result;
    while(sw==0){
        int i = 0;
        while(i<number_of_all && sw == 0){
            if(list[i].energy>0)mapprinter(world , 20 , list[i]);

            if(list[i].gender == controlanimal){
                if(list[i].energy>0){
                    printf("You Are In Position(%d,%d) with %d energy\n " , list[i].x , list[i].y,list[i].energy);
                    do{
                        printf("which activity do you want?!(move\\donat\\fight)\n");
                        scanf("%s",Activity);
                        if(strcmp(Activity,"donate")!=0 && strcmp(Activity,"move")!=0 && strcmp(Activity,"fight")!=0){
                            printf("please answer with (move\\fight\\donate\n");
                        }
                    }while(strcmp(Activity,"donate")!=0 && strcmp(Activity,"move")!=0 && strcmp(Activity,"fight")!=0);


                    if(strcmp(Activity,"move")==0){
                        int number_movements;
                        do{
                            printf("please eneter your dierction:\n");
                            scanf(" %c",&direc);
                            printf("please enter number of direction:\n");
                            scanf("%d",&number_movements);
                            while(number_movements>list[i].numberm || list[i].energy<number_movements*list[i].movemente){
                                printf("please decrease number of your movements\n");
                                scanf("%d",&number_movements);
                            }
                            result = movethiky(&list[i] , direc , number_movements);
                            if(result==-1){
                                printf("ERROR: please enter another direction ");
                            }
                        }while(result == -1);
                        if(list[i].energy<list[i].movemente){
                            world[list[i].x][list[i].y]='F';
                            Food_energy[NumberFood]=list[i].energy;
                            Food_Position[NumberFood*2]=list[i].x;
                            Food_Position[NumberFood*2+1]=list[i].y;
                            NumberFood++;
                            list[i].energy=0;
                        }
                        i++;
                    }
                    else if(strcmp(Activity,"donate")==0){
                        int x,y;
                        int j;
                        do{
                            printf("please enetr position of animal that you want to donat to it:\n");
                            scanf("%d %d",&x,&y);
                            j = serach_for_animal(list,x,y);
                            if(list[j].gender!=controlanimal){
                                printf("you can't donate to this creature!!\n");
                            }
                            if(j==-1){
                                printf("this animal isn't available!!!\n");
                            }
                        }while(j==-1 || list[j].gender!=controlanimal);
                        list[i].energy -= list[i].movemente;
                        list[j].energy += list[i].movemente;
                        if(list[i].energy<list[i].movemente){
                            world[list[i].x][list[i].y]='F';
                            Food_energy[NumberFood]=list[i].energy;
                            Food_Position[NumberFood*2]=list[i].x;
                            Food_Position[NumberFood*2+1]=list[i].y;
                            NumberFood++;
                            list[i].energy=0;
                        }
                        i++;
                    }
                    else {
                        char answer[4];
                        int x,y;
                        int j;
                       if(list[i].energy >= 3*list[i].movemente){
                            printf("please enter position of animal that you want to attack to it:\n");
                            do{
                                scanf("%d %d",&x,&y);
                                j=serach_for_animal(list,x,y);
                                if(list[j].gender==controlanimal){
                                    printf("you can't attack to this creature!!!\n please enter another position:\n");
                                }
                                if(j==-1){
                                    printf("this animal isn't available!!!\n please enter another position:\n");
                                } 
                            }while(j==-1 || list[j].gender==controlanimal);
                            if(list[i].attacke > list[j].defense){
                                setTextColor(14,0);
                                printf("creature <<%c>> won in attack :)\n ",controlanimal);
                                setTextColor(11,0);
                                list[i].energy += list[j].energy;
                                list[j].energy=0;
                                world[list[j].x][list[j].y]='-';
                            }
                            else if(list[i].attacke < list[j].defense){
                                setTextColor(14,0);
                                printf("creature <<%c>> won in attack :(\n",list[j].gender);
                                setTextColor(11,0);
                                list[j].energy += list[i].energy;
                                list[i].energy=0;
                                world[list[i].x][list[i].y]='-';
                            }
                            if(list[i].energy < list[i].movemente && list[i].energy>0){
                                Food_energy[NumberFood]=list[i].energy;
                                Food_Position[NumberFood*2]=list[i].x;
                                Food_Position[NumberFood*2+1]=list[i].y;
                                NumberFood++;
                                list[i].energy=0;
                            }
                        }
                       i++;
                    }    
                }
                else{
                    i++;
                }    
            }
            else{
                int donate_result = -1;
                donate_result = donate(&list[i]);
                int attack_result = -1;
                production_result = 0;
                if(list[i].energy > 3*list[i].movemente && donate_result == -1){
                    attack_result =  attack(&list[i]);
                    
                }
                if(list[i].energy > list[i].productione && attack_result == -1 && donate_result == -1) production_result = production(&list[i]);
                if (production_result!=1 && attack_result == -1 && donate_result == -1){
                    theNearest(list[i].x , list[i].y , 'H');
                    sleep(1000);
                    printf("Moving creature %c in (%d,%d) to (%d,%d)" , list[i].gender , list[i].x , list[i].y , nearest[0] , nearest[1]);
                    result = moveUnc(&list[i]);
                }
                
                i++;
            }
    
        }
    }
    if(sw == 1) {
        printf("\nG , Wp all. Creture %c won !!\nPress Any key to exit" , winner);
        getch();
    }









}
