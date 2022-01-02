#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

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
void setTextColor(int textColor, int backColor) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle, colorAttribute);

}


void sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void clearScreen() {
    system("clear");
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

}


void mapprinter(char world[][20],int size){
    printf("\n");
    for(int i=0;i<size;i++){
        printf("|");
        for(int j=0;j<size;j++){

            printf("%c|",world[i][j]);
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




void movewithkey( int n , int animaltype[150] , char direc , int* i){
    moved = 1;
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
            printf("\aERROR:please enter another direction\n");
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
            printf("\aERROR:please enter another direction\n");
            *i-=2;
        }
    }
    else if(direc=='d'){
        move_direction = 'd';
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
            printf("\aERROR:please enter another direction\n");
            *i-=2;
        }
    }
    else if(direc=='x'){
        move_direction = 'x';
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
            printf("\aERROR:please enter another direction\n");
            *i-=2;
        }
    }
    else if(direc=='q'){
        move_direction = 'q';
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
            printf("\aERROR:please enter another direction\n");
            *i-=2;
        }
    }
    else if(direc=='e'){
        move_direction = 'e';
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
            printf("\aERROR:please enter another direction\n");
            *i-=2;
        }
    }
    else if(direc=='c'){
        move_direction = 'c';
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
            printf("\aERROR:please enter another direction\n");
            *i-=2;
        }
    }
    else if(direc=='z'){
        move_direction = 'z';
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
                printf("\aERROR:please enter another direction\n");
                *i-=2;
            }
        }
    else{
        moved = 0;
        printf("\athis direction isn't available!!\n");
        *i-=2;
    }
    *i += 2;
    mapprinter(world,size);
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

void moveunc(int x , int y , int number , int j){
    if(x>unc[0]){
        if(y>unc[1]){
            if(world[x-1][y-1] == '-' || world[x-1][y-1] == 'H')movewithkey(number , noncanimals , 'q' , &j);
            else if (world[x-1][y] == '-'|| world[x-1][y] == 'H') movewithkey(number , noncanimals , 'a' , &j);
            else if ((world[x][y-1] == '-'|| world[x][y-1] == 'H')) movewithkey(number , noncanimals , 'x' , &j);
        }
        if(y<unc[1]){
            if(world[x-1][y+1] == '-'|| world[x-1][y+1] == 'H')movewithkey(number , noncanimals , 'e' , &j);
            else if(world[x][y+1] == '-'|| world[x][y+1] == 'H')movewithkey(number , noncanimals , 'd' , &j);
            else if(world[x-1][y] == '-'|| world[x-1][y] == 'H')movewithkey(number , noncanimals , 'w' , &j);
        }
        if(y==unc[1]){
            if(world[x-1][y] == '-'|| world[x-1][y] == 'H')movewithkey(number , noncanimals , 'w' , &j);
            else if(world[x-1][y+1]=='-'|| world[x-1][y+1] == 'H') movewithkey(number , noncanimals , 'e' , &j);
            else if(world[x+1][y+1]=='-'|| world[x+1][y+1] == 'H') movewithkey(number , noncanimals , 'c' , &j);
        }
    }
    if(x<unc[0]){
        if(y>unc[1]){
            if(world[x+1][y-1] == '-'|| world[x+1][y-1] == 'H' )movewithkey(number , noncanimals , 'z' , &j);
            else if(world[x+1][y] == '-'|| world[x+1][y] == 'H')movewithkey(number , noncanimals , 'x' , &j);
            else if(world[x][y-1] == '-'|| world[x][y-1] == 'H')movewithkey(number , noncanimals , 'a' , &j);
        
        }
        if(y<unc[1]){
            if(world[x+1][y+1] == '-'|| world[x+1][y+1] == 'H')movewithkey(number , noncanimals , 'c' , &j);
            else if(world[x+1][y] == '-'|| world[x+1][y] == 'H')movewithkey(number , noncanimals , 'x' , &j);
            else if(world[x][y+1] == '-'|| world[x+1][y+1] == 'H')movewithkey(number , noncanimals , 'd' , &j);
        }
        if(y==unc[1]){
            if(world[x+1][y] == '-'|| world[x+1][y] == 'H')movewithkey(number , noncanimals , 'x' , &j);
            else if(world[x+1][y-1] == '-'|| world[x+1][y-1] == 'H')movewithkey(number , noncanimals , 'z' , &j);
            else if(world[x+1][y+1] == '-'|| world[x+1][y+1] == 'H')movewithkey(number , noncanimals , 'c' , &j);
        }
    }
    if(x==unc[0]){
        if(y>unc[1]){
            if(world[x][y-1] == '-'|| world[x][y-1] == 'H')movewithkey(number , noncanimals , 'a' , &j);
            else if(world[x-1][y-1] == '-'|| world[x-1][y+1] == 'H')movewithkey(number , noncanimals , 'q' , &j);
            else if(world[x+1][y-1] == '-'|| world[x+1][y-1] == 'H')movewithkey(number , noncanimals , 'z' , &j);
        
        }
        if(y<unc[1]){
            if(world[x][y+1] == '-'|| world[x][y+1] == 'H')movewithkey(number , noncanimals , 'd' , &j);
            else if(world[x-1][y+1]=='-'|| world[x-1][y+1] == 'H') movewithkey(number , noncanimals , 'e' , &j);
            else if(world[x+1][y+1] == '-'|| world[x+1][y+1] == 'H')movewithkey(number , noncanimals , 'c' , &j);
        }
    }
}

int main(){

    FILE *log;
    log = fopen("game-log.txt" , "wt");
    FILE *readfile;
    int c[2];

    readfile = fopen("C:\\creatures_to_heaven\\map-phase0.txt" , "rt" );
    if(!readfile || !log) printf("File did not open!");
    setTextColor(11 , 0);
    mapreader(readfile);
    //log the map;
    for(int i=0;i<size;i++){
        fprintf(log , "|");
        for(int j=0;j<size;j++){
            fprintf(log ,"%c|",world[i][j]);
        }
        fprintf(log , "\n");
    }
    fprintf(log , "\n");
    mapprinter(world,size);
    printf("MOVE with:\n");
    printf("          q -- w -- e\n");
    printf("          |    |    |\n");
    printf("          a -- @ -- d\n");
    printf("          |    |    |\n");
    printf("          z -- x -- c\n");

    printf("\n");
    int ch;
    int n=0;
    int number = 0;
    ch=fgetc(readfile);
    printf("The Creature under your control : %c\n",ch);


    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){

            if(world[i][j]==ch){
                panimal[n]=i;
                panimal[n+1]=j;
                n +=2;
            }
        }
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){

            if(world[i][j] != ch && world[i][j] != 'H' && world[i][j] != '#' && world[i][j] != '-'){
                noncanimals[number]=i;
                noncanimals[number+1]=j;
                number+=2;
            }
        }
    }

    
    while(sw==0){
        int i = 0;
        while(i<n && sw ==0){
            animal = ch;
            
            printf("you are at position:(%d,%d)\n",panimal[i],panimal[i+1]);
            int x1 = panimal[i];
            int y1 = panimal[i+1];
            moving_creature = world[x1][y1];
            printf("please enter your direction of movement:\n");
            scanf(" %c" , &direc);
            movewithkey( n , panimal , direc , &i );
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
            theNearest(noncanimals[j] , noncanimals[j+1] , 'H');
            int x = noncanimals[j];
            int y = noncanimals[j+1];
            animal = world[x][y];
            printf("moving creature %c in position(%d,%d) to (%d,%d) : \n" , world[x][y] ,x , y , unc[0] , unc[1]);
            moveunc(x , y , number , j);
            fprintf(log , "moving creature %c in (%d,%d) into %c direction\n" , animal ,x , y , move_direction );
            if(sw==1) {
                printf("gg , wp all -> creature %c won!!!",winner);
                fprintf( log, "gg , wp all -> creature %c won!!!",winner);
            }
            j += 2;
            sleep(1000);
            

        }
    
    
    
    
    
    
    
    }



    
}
