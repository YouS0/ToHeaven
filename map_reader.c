#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

char lines[100];
char world[20][20];
int heaven_cords[100];
int size;
int heavens;
int creatures_cord[200];
int numberOfCreatures=0;
int deadend_cords[200];
int deadends;
int position;
int panimal[150];
int noncanimals[150];
char winner;
int sw = 0;
char direc;
char animal;
int unc[2];
int moved = 1;
char moving_creature;
char move_direction;
int controlanimal;
char ch;
int movements ;
int move_switch;
int unc_possible_move;
void setTextColor(int textColor, int backColor) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle, colorAttribute);

}


void sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
  

struct sanimal{
    char gender;
    int primarye;  //primary energy
    int movemente; //movement energy 
    int numberm; //number of movement
    int productione;  
    int attacke;   
    int defense;
}list[10]; //it is supposed that number of maximum creatures is 10

int search(struct sanimal a[],int ch){

    for(int i=0;i<10;i++){
        if(a[i].gender==ch) return i;
    }
}

void mapreader(FILE *readfile){
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
    while (k!=2){
        fgets(lines , 100 ,readfile);
        if(strcmp(lines , endofline)==0)k++;
    }
    fgets(lines , 100 ,readfile);
    while(strcmp(lines,endofline)!=0){
        numberOfCreatures = atof(&lines[2]);
        position = 0;
        for(int i = 5 ; i<strlen(lines);i++){
            if(lines[i]>='0' && lines[i]<='9') {
                creatures_cord[position] = atof(&lines[i]);
                position +=1;
                if(atof(&lines[i])>=10)i++;
            }
        }
        for(int j = 0 ; j<2*numberOfCreatures ; j++){
            world[creatures_cord[j]][creatures_cord[j+1]] = lines[0];
            j++;
        }
        fgets(lines , 100 ,readfile);
    }
    controlanimal=fgetc(readfile);
    fgetc(readfile);
    fscanf(readfile,"%s",endofline);

    int i=0;
    while(!feof(readfile)){

        fscanf(readfile," %c",&list[i].gender);
        fscanf(readfile,"%d",&list[i].primarye);
        fscanf(readfile,"%d$",&list[i].movemente);
        fscanf(readfile,"%d$",&list[i].numberm);
        fscanf(readfile,"%d$",&list[i].productione);
        fscanf(readfile,"%d$",&list[i].attacke);
        fscanf(readfile,"%d",&list[i].defense);

        i++;
    }   

}


void mapprinter(char world[][20],int size,int k,int z){
    printf("\n");
    for(int i=0;i<size;i++){
        setTextColor(11,0);
        printf("|");
        for(int j=0;j<size;j++){
            if(i==k && j==z){
                setTextColor(14,0);
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

void movewithkey(int animaltype[150] , char direc , int* i){
    moved=1;
    if(direc=='a'){
        move_direction = 'a';
        if(world[animaltype[*i]][animaltype[*i+1]-1]=='-'){
            swap(world,animaltype[*i],animaltype[*i+1],animaltype[*i],animaltype[*i+1]-1);
            animaltype[*i+1]-=1;
        }
        else if(world[animaltype[*i]][animaltype[*i+1]-1]=='H'){
            winner = animal;
            sw=1;
            //world[animaltype[*i]][animaltype[*i+1]-1]=world[animaltype[*i]][animaltype[*i+1]];
            world[animaltype[*i]][animaltype[*i+1]]='-';
        }
        else{
            moved = 0;
            *i-=2;
        }
    }
    else if(direc=='w'){
        move_direction = 'w';
        if(world[animaltype[*i]-1][animaltype[*i+1]]=='-'){
            swap(world,animaltype[*i]-1,animaltype[*i+1],animaltype[*i],animaltype[*i+1]);
            animaltype[*i]-=1;
        }
        else if(world[animaltype[*i]-1][animaltype[*i+1]]=='H'){
            winner = animal;
            sw=1;
            //world[animaltype[*i]-1][animaltype[*i+1]]=world[animaltype[*i]][animaltype[*i+1]];
            world[animaltype[*i]][animaltype[*i+1]]='-';
        }
        else{
            moved = 0;
            *i-=2;
        }
    }
    else if(direc=='d'){
        move_direction='d';
        if(world[animaltype[*i]][animaltype[*i+1]+1]=='-'){
            swap(world,animaltype[*i],animaltype[*i+1]+1,animaltype[*i],animaltype[*i+1]);
            animaltype[*i+1]+=1;
        }
        else if(world[animaltype[*i]][animaltype[*i+1]+1]=='H'){
            winner = animal;
            sw=1;
            //world[animaltype[*i]][animaltype[*i+1]+1]=world[animaltype[*i]][animaltype[*i+1]];
            world[animaltype[*i]][animaltype[*i+1]]='-';
        }
        else{
            moved = 0;
            *i-=2;
        }
    }
    else if(direc=='x'){
        move_direction='x';
        if(world[animaltype[*i]+1][animaltype[*i+1]]=='-'){
            swap(world,animaltype[*i]+1,animaltype[*i+1],animaltype[*i],animaltype[*i+1]);
            animaltype[*i]+=1;
        }
        else if(world[animaltype[*i]+1][animaltype[*i+1]]=='H'){
            winner = animal;
            sw=1;
            //world[animaltype[*i]+1][animaltype[*i+1]]=world[animaltype[*i]][animaltype[*i+1]];
            world[animaltype[*i]][animaltype[*i+1]]='-';
        }
        else{
            moved = 0;
            *i-=2;
        }
    }
    else if(direc=='q'){
        move_direction='q';
        if(world[animaltype[*i]-1][animaltype[*i+1]-1]=='-'){
            swap(world,animaltype[*i]-1,animaltype[*i+1]-1,animaltype[*i],animaltype[*i+1]);
            animaltype[*i]-=1;
            animaltype[*i+1]-=1;
        }
        else if(world[animaltype[*i]-1][animaltype[*i+1]-1]=='H'){
            winner = animal;
            sw=1;
            //world[animaltype[*i]-1][animaltype[*i+1]-1]=world[animaltype[*i]][animaltype[*i+1]];
            world[animaltype[*i]][animaltype[*i+1]]='-';
        }
        else{
            moved = 0;
            *i-=2;
        }
    }
    else if(direc=='e'){
        move_direction='e';
        if(world[animaltype[*i]-1][animaltype[*i+1]+1]=='-'){
            swap(world,animaltype[*i]-1,animaltype[*i+1]+1,animaltype[*i],animaltype[*i+1]);
            animaltype[*i]-=1;
            animaltype[*i+1]+=1;
        }
        else if(world[animaltype[*i]-1][animaltype[*i+1]+1]=='H'){
            winner = animal;
            sw=1;
            //world[animaltype[*i]-1][animaltype[*i+1]+1]=world[animaltype[*i]][animaltype[*i+1]];
            world[animaltype[*i]][animaltype[*i+1]]='-';
        }
        else{
            moved = 0;
            *i-=2;
        }
    }
    else if(direc=='c'){
        move_direction='c';
        if(world[animaltype[*i]+1][animaltype[*i+1]+1]=='-'){
            swap(world,animaltype[*i]+1,animaltype[*i+1]+1,animaltype[*i],animaltype[*i+1]);
            animaltype[*i]+=1;
            animaltype[*i+1]+=1;
        }
        else if(world[animaltype[*i]+1][animaltype[*i+1]+1]=='H'){
            winner = animal;
            sw=1;
            //world[animaltype[*i]+1][animaltype[*i+1]+1]=world[animaltype[*i]][animaltype[*i+1]];
            world[animaltype[*i]][animaltype[*i+1]]='-';
        }
        else{
            moved = 0;
            *i-=2;
        }
    }
    else if(direc=='z'){
        move_direction='z';
        if(world[animaltype[*i]+1][animaltype[*i+1]-1]=='-'){
                swap(world,animaltype[*i]+1,animaltype[*i+1]-1,animaltype[*i],animaltype[*i+1]);
                animaltype[*i]+=1;
                animaltype[*i+1]-=1;
            }
            else if(world[animaltype[*i]+1][animaltype[*i+1]-1]=='H'){
                winner = animal;
                sw=1;
                //world[animaltype[*i]+1][animaltype[*i+1]-1]=world[animaltype[*i]][animaltype[*i+1]];
                world[animaltype[*i]][animaltype[*i+1]]='-';
            }
            else{
                moved = 0;
                *i-=2;
            }
    }
    else{
        moved = 0;
        *i-=2;
    }
   // mapprinter(world,size,animaltype[*i],animaltype[*i+1]);
}


void movewithkey2( int n , int animaltype[150] , char direc , int* i){
    moved = 1;
    if(direc=='a'){
        move_direction = 'a';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]][animaltype[*i+1]-j]=='-' ||world[animaltype[*i]][animaltype[*i+1]-j]=='H'){
                j++;
            }
            else{
                break;
            }
        }
        j--;
        if(j==0){
            moved = 0;
            setTextColor(4,0);
            printf("\aERROR:please enter another direction\n");
            setTextColor(11,0);
            *i-=2;
        }
        else{
            printf("you can have only ((%d)) movementes through this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
            }while (n>j);

            if(world[animaltype[*i]][animaltype[*i+1]-n]=='-'){
               swap(world,animaltype[*i],animaltype[*i+1],animaltype[*i],animaltype[*i+1]-n);
               animaltype[*i+1]-=n; 
            }

            else{
                winner = animal;
                sw=1;
                world[animaltype[*i]][animaltype[*i+1]]='-';
            }
        }
    }
    else if(direc=='w'){
        move_direction = 'w';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]-j][animaltype[*i+1]]=='-' ||world[animaltype[*i]-j][animaltype[*i+1]]=='H'){
                j++;
            }
            else{
                break;
            }
        }
        j--;
        if(j==0){
            moved = 0;
            setTextColor(4,0);
            printf("\aERROR:please enter another direction\n");
            setTextColor(11,0);
            *i-=2;
        }
        else{
            printf("you can have only ((%d)) movementes through this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
            }while (n>j);

            if(world[animaltype[*i]-n][animaltype[*i+1]]=='-'){
               swap(world,animaltype[*i],animaltype[*i+1],animaltype[*i]-n,animaltype[*i+1]);
               animaltype[*i]-=n; 
            }

            else{
                winner = animal;
                sw=1;
                world[animaltype[*i]][animaltype[*i+1]]='-';
            }
        }

    }
    else if(direc=='d'){
        move_direction = 'd';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]][animaltype[*i+1]+j]=='-' || world[animaltype[*i]][animaltype[*i+1]+j]=='H'){
                j++;
            }
            else{
                break;
            }
        }
        j--;

        if(j==0){
            moved = 0;
            setTextColor(4,0);
            printf("\aERROR:please enter another direction\n");
            setTextColor(11,0);
            *i-=2; 
        }
        else{
            printf("you can have only ((%d)) movementes through this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
            }while (n>j);

            if(world[animaltype[*i]][animaltype[*i+1]+n]=='-'){
               swap(world,animaltype[*i],animaltype[*i+1]+n,animaltype[*i],animaltype[*i+1]);
               animaltype[*i+1]+=n; 
            } 
            else{
               winner = animal;
               sw=1;
               world[animaltype[*i]][animaltype[*i+1]]='-'; 
            }
        }
    }
    else if(direc=='x'){
        move_direction = 'x';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]+j][animaltype[*i+1]]=='-' || world[animaltype[*i]+j][animaltype[*i+1]]=='H'){
                j++;
            }
            else{
                break;
            }
        }
        j--;

        if(j==0){
            moved = 0;
            setTextColor(4,0);
            printf("\aERROR:please enter another direction\n");
            setTextColor(11,0);
            *i-=2;
        }
        else{
            printf("you can have only ((%d)) movementes through this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
            }while (n>j);

            if(world[animaltype[*i]+n][animaltype[*i+1]]=='-'){
                swap(world,animaltype[*i]+n,animaltype[*i+1],animaltype[*i],animaltype[*i+1]);
                animaltype[*i]+=n;  
            }
            else{
                winner = animal;
                sw=1;
                world[animaltype[*i]][animaltype[*i+1]]='-';
            }
        }
    }
    else if(direc=='q'){
        move_direction = 'q';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]-j][animaltype[*i+1]-j]=='-' || world[animaltype[*i]-j][animaltype[*i+1]-j]=='H'){
                j++;
            }
            else{
                break;
            }
        }
        j--;

        if(j==0){
            moved = 0;
            setTextColor(4,0);
            printf("\aERROR:please enter another direction\n");
            setTextColor(11,0);
            *i-=2;
        }
        else{
            printf("you can have only ((%d)) movementes through this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
            }while (n>j);

            if(world[animaltype[*i]-j][animaltype[*i+1]-j]=='-' ){
                swap(world,animaltype[*i]-n,animaltype[*i+1]-n,animaltype[*i],animaltype[*i+1]);
                animaltype[*i]-=n;
                animaltype[*i+1]-=n;  
            }
            else{
               winner = animal;
               sw=1;
               world[animaltype[*i]][animaltype[*i+1]]='-'; 
            }
        }
    }
    else if(direc=='e'){
        move_direction = 'e';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]-j][animaltype[*i+1]+j]=='-' || world[animaltype[*i]-j][animaltype[*i+1]+j]=='H'){
                j++;
            }
            else{
                break;
            }
        }
        j--;

        if(j==0){
            moved = 0;
            setTextColor(4,0);
            printf("\aERROR:please enter another direction\n");
            setTextColor(11,0);
            *i-=2;
        }
        else{
           printf("you can have only ((%d)) movementes through this direction \n",j);
           do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
            }while (n>j);

           if(world[animaltype[*i]-n][animaltype[*i+1]+n]=='-'){
               swap(world,animaltype[*i]-n,animaltype[*i+1]+n,animaltype[*i],animaltype[*i+1]);
               animaltype[*i]-=n;
               animaltype[*i+1]+=n;
           } 
           else{
              winner = animal;
              sw=1;
              world[animaltype[*i]][animaltype[*i+1]]='-'; 
           }
        }
    }
    else if(direc=='c'){
        move_direction = 'c';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]+j][animaltype[*i+1]+j]=='-' || world[animaltype[*i]+j][animaltype[*i+1]+j]=='H'){
                j++;
            }
            else{
                break;
            }
        }
        j--;
        
        if(j==0){
            moved = 0;
            setTextColor(4,0);
            printf("\aERROR:please enter another direction\n");
            setTextColor(11,0);
            *i-=2;
        }
        else{
            printf("you can have only ((%d)) movementes through this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
            }while (n>j);

            if(world[animaltype[*i]+n][animaltype[*i+1]+n]=='-'){
                swap(world,animaltype[*i]+n,animaltype[*i+1]+n,animaltype[*i],animaltype[*i+1]);
                animaltype[*i]+=n;
                animaltype[*i+1]+=n;
            }
            else{
               winner = animal;
               sw=1;
               world[animaltype[*i]][animaltype[*i+1]]='-'; 
            }
        }
    }
    else if(direc=='z'){
        move_direction = 'z';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]+j][animaltype[*i+1]-j]=='-' || world[animaltype[*i]+j][animaltype[*i+1]-j]=='H'){
                j++;
            }
            else{
                break;
            }
        }
        j--;

        if(j==0){
            moved = 0;
            setTextColor(4,0);
            printf("\aERROR:please enter another direction\n");
            setTextColor(11,0);
            *i-=2;
        }
        else{
            printf("you can have only ((%d)) movementes through this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
            }while (n>j);

            if(world[animaltype[*i]+n][animaltype[*i+1]-n]=='-'){
               swap(world,animaltype[*i]+1,animaltype[*i+1]-1,animaltype[*i],animaltype[*i+1]);
               animaltype[*i]+=1;
               animaltype[*i+1]-=1; 
            }
            else{
               winner = animal;
               sw=1;
               world[animaltype[*i]][animaltype[*i+1]]='-'; 
            }
        }
        }
    else{
        moved = 0;
        setTextColor(4,0);
        printf("\athis direction isn't available!!\n");
        setTextColor(11,0);
        *i-=2;
    }
    *i += 2;
   // mapprinter(world,size,animaltype[*i],animaltype[*i+1]);
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
                    unc[0] = i;
                    unc[1] = j;
                }
            }
        }
    }
    
}

void moveunc(int j){
    int x = noncanimals[j];
    int y = noncanimals[j+1];
    
    if(x>unc[0]){
        if(y>unc[1]){
            if(world[x-1][y-1] == '-' || world[x-1][y-1] == 'H')while(movements<unc_possible_move && sw == 0) movewithkey(noncanimals , 'q' , &j), movements++;
            else if (world[x-1][y] == '-'|| world[x-1][y] == 'H') while(movements<unc_possible_move)movewithkey(noncanimals , 'a' , &j), movements++;
            else if ((world[x][y-1] == '-'|| world[x][y-1] == 'H')) while(movements<unc_possible_move)movewithkey(noncanimals , 'x' , &j), movements++;
        }
        if(y<unc[1]){
            if(world[x-1][y+1] == '-'|| world[x-1][y+1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'e' , &j), movements++;
            else if(world[x][y+1] == '-'|| world[x][y+1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'd' , &j), movements++;
            else if(world[x-1][y] == '-'|| world[x-1][y] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'w' , &j), movements++;
        }
        if(y==unc[1]){
            if(world[x-1][y] == '-'|| world[x-1][y] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'w' , &j), movements++;
            else if(world[x-1][y+1]=='-'|| world[x-1][y+1] == 'H') while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'e' , &j), movements++;
            else if(world[x+1][y+1]=='-'|| world[x+1][y+1] == 'H') while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'c' , &j), movements++;
        }
    }
    if(x<unc[0]){
        if(y>unc[1]){
            if(world[x+1][y-1] == '-'|| world[x+1][y-1] == 'H' )while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'z' , &j), movements++;
            else if(world[x+1][y] == '-'|| world[x+1][y] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'x' , &j), movements++;
            else if(world[x][y-1] == '-'|| world[x][y-1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'a' , &j), movements++;
        }
        if(y<unc[1]){
            if(world[x+1][y+1] == '-'|| world[x+1][y+1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'c' , &j), movements++;
            else if(world[x+1][y] == '-'|| world[x+1][y] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'x' , &j), movements++;
            else if(world[x][y+1] == '-'|| world[x+1][y+1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'd' , &j), movements++;
        }
        if(y==unc[1]){
            if(world[x+1][y] == '-'|| world[x+1][y] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'x' , &j), movements++;
            else if(world[x+1][y-1] == '-'|| world[x+1][y-1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'z' , &j), movements++;
            else if(world[x+1][y+1] == '-'|| world[x+1][y+1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'c' , &j), movements++;
        }
    }
    if(x==unc[0]){
        if(y>unc[1]){
            if(world[x][y-1] == '-'|| world[x][y-1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'a' , &j), movements++;
            else if(world[x-1][y-1] == '-'|| world[x-1][y+1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'q' , &j), movements++;
            else if(world[x+1][y-1] == '-'|| world[x+1][y-1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'z' , &j), movements++;
        }
        if(y<unc[1]){
            if(world[x][y+1] == '-'|| world[x][y+1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'd' , &j), movements++;
            else if(world[x-1][y+1]=='-'|| world[x-1][y+1] == 'H') while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'e' , &j) , movements++;
            else if(world[x+1][y+1] == '-'|| world[x+1][y+1] == 'H')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'c' , &j) , movements++;
        }
    }
    
    
}

int main(){

    FILE *log;
    log = fopen("game-log.txt" , "wt");
    FILE *readfile;
    int c[2];

    readfile = fopen("map-phase1.txt" , "rt" );
    if(!readfile || !log) printf("File did not open!");
    mapreader(readfile);
    for(int i=0;i<size;i++){
        fprintf(log , "|");
        for(int j=0;j<size;j++){
            fprintf(log ,"%c|",world[i][j]);
        }
        fprintf(log , "\n");
    }
    fprintf(log , "\n");
    /*mapprinter2(world,size);

    printf("\n");*/
    setTextColor(11,0);
    int n=0;
    int number = 0;
    printf("\n");
    printf("The Creature under your control : %c\n",controlanimal);



    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){

            if(world[i][j]==controlanimal){
                panimal[n]=i;
                panimal[n+1]=j;
                n +=2;
            }
        }
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){

            if(world[i][j] != controlanimal && world[i][j] != 'H' && world[i][j] != '#' && world[i][j] != '-'){
                noncanimals[number]=i;
                noncanimals[number+1]=j;
                number+=2;
            }
        }
    }

    int z=search(list,controlanimal); //getting place of controlled creature in array "list".

    while(sw==0){
        int i = 0;
        while(i<n && sw ==0){
            animal = controlanimal;

            printf("you are at position:(%d,%d)\n",panimal[i],panimal[i+1]);
            int x1 = panimal[i];
            int y1 = panimal[i+1];
            mapprinter(world,size,x1,y1);
            moving_creature = world[x1][y1];
            printf("please enter direction of your movement:\n");
            scanf(" %c" , &direc);
            movewithkey2( list[z].numberm , panimal , direc , &i );
            if(moved == 1){
                fprintf(log , "moving creature %c in (%d,%d) into %c direction\n" , moving_creature, x1 , y1 , move_direction );
            }
            if(sw==1) {
                printf("gg , wp all -> creature %c won!!!",winner);
                fprintf( log, "gg , wp all -> creature %c won!!!",winner);
            }
        }
        int j = 0;
        while(j<number && sw ==0){
            movements = 0;
            theNearest(noncanimals[j] , noncanimals[j+1] , 'H');
            int x = noncanimals[j];
            int y = noncanimals[j+1];
            animal = world[x][y];
            unc_possible_move = list[search(list,animal)].numberm;
            printf("moving creature %c in position(%d,%d) to (%d,%d) : \n" , world[x][y] ,x , y , unc[0] , unc[1]);
            mapprinter(world,size,x,y);
            moveunc(j);
            fprintf(log , "moving creature %c in (%d,%d) into %c direction\n" , animal ,x , y , move_direction );
            sleep(1000);
            j += 2;
            if(sw==1){
                printf("gg , wp all -> creature %c won!!!",winner);
                fprintf( log, "gg , wp all -> creature %c won!!!",winner);
            }

        }
    
    
    
    
    
    
    
    }
    printf("\nPress Any Key To Exit");
    getch();


    
}
