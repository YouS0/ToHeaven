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
int Food_Position[100];
int Food_energy[100];
int NumberFood=0;
int SwforAnimal[100]={0};
char winner;
int sw = 0;
char direc;
char animal;
int unc[2];
int moved = 1;
char moving_creature;
char move_direction;
int controlanimal;
int movements ;
int move_switch;
int unc_possible_move;
void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorCoord;
    cursorCoord.X = y;
    cursorCoord.Y = x;
    SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

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
    int n;    //number of animal
    char gender;
    int energy[20];  //it is supposed that number of maximum animals is 20
    int movemente;  //movement energy 
    int numberm;   //number of movement
    int productione;  
    int attacke;   
    int defense;

}list[10]; //it is supposed that number of maximum creatures is 10

int SearchFood(int i,int j){
    for(int k=0;k<NumberFood*2;k+=2){
        if(Food_Position[k]==i && Food_Position[k+1]==j) return k;
    }
    return -1;
}

int search(struct sanimal a[],int ch){

    for(int i=0;i<10;i++){
        if(a[i].gender==ch) return i;
    }
}//search for place of creatures in array "list"

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
    
    /*while (k!=2){
        fgets(lines , 100 ,readfile);
        if(strcmp(lines , endofline)==0)k++;
    }*/
    char endofline[]="===\n";
    int k = 0;
    int i=0;
    char ch;
    fscanf(readfile,"%s\n",&endofline);
    fscanf(readfile,"%c",&ch);
    while (ch=='F')
    {
    fscanf(readfile,"%d ",&Food_energy[k]);
    fscanf(readfile,"%c",&ch);
    fscanf(readfile,"%d",&Food_Position[i]);
    fscanf(readfile,"%c",&ch);
    fscanf(readfile,"%d",&Food_Position[i+1]);
    fscanf(readfile,"%c\n",&ch);
    fscanf(readfile,"%c",&ch);
    k++,i+=2,NumberFood++;
    }
    for(int i = 0 ; i < NumberFood ; i++){
        world[Food_Position[i]][Food_Position[i+1]] = 'F';
    }
    fscanf(readfile,"%c%c\n",&ch,&ch);

    strcpy(endofline,"===\n");
    fgets(lines , 100 ,readfile);
    k=0;
    while(strcmp(lines,endofline)!=0){
        numberOfCreatures = atof(&lines[2]);
        (list[k].n)=numberOfCreatures;
        k++;
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

    i=0;
    while(!feof(readfile)){

        fscanf(readfile," %c",&list[i].gender);
        fscanf(readfile,"%d",&list[i].energy[0]);
        for(int j=1;j<(list[i].n);j++){
            (list[i].energy[j])=(list[i].energy[0]);
        }
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
    for(int i = 0 ; i<NumberFood , Food_energy[i] > 0 ; i++){
        printf("Food (%d,%d) has %d\n" , Food_Position[2*i] , Food_Position[2*i+1] , Food_energy[i]);
    }
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
}


void movewithkey2( int place , int animaltype[150] , char direc , int* i , char animal){
    int n=list[place].numberm;
    int Energy=list[place].movemente;
    moved = 1;
    if(direc=='a'){
        move_direction = 'a';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]][animaltype[*i+1]-j]=='-' ||world[animaltype[*i]][animaltype[*i+1]-j]=='H' || world[animaltype[*i]][animaltype[*i+1]-j]=='F'){
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
            printf("you can have only ((%d)) movementes along this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
                if(n*Energy > list[place].energy[(*i)/2]){
                    setTextColor(4,0);
                    printf("your energy isn't enough for this movement!!!\n");
                    printf("please decrease number of your movement\n");
                    setTextColor(11,0);
                }
            }while (n>j || n*Energy > list[place].energy[(*i)/2]);

            int EFood=SearchFood(animaltype[*i],animaltype[*i+1]-n);
            if(world[animaltype[*i]][animaltype[*i+1]-n]=='-'){
               swap(world,animaltype[*i],animaltype[*i+1],animaltype[*i],animaltype[*i+1]-n);
               animaltype[*i+1]-=n; 
            }
            else if(world[animaltype[*i]][animaltype[*i+1]-n]=='F'){
                world[animaltype[*i]][animaltype[*i+1]] = '-';
                world[animaltype[*i]][animaltype[*i+1]-n] = animal;
                list[place].energy[*i/2]+=Food_energy[EFood];
                Food_energy[EFood] = 0;
                animaltype[*i+1]-=n; 
            }
            else{
                winner = animal;
                sw=1;
                world[animaltype[*i]][animaltype[*i+1]]='-';
            }
           list[place].energy[(*i)/2]-=n*Energy;
           if(list[place].energy[(*i)/2]<Energy){
               SwforAnimal[(*i)/2]=1;
               Food_energy[NumberFood]=list[place].energy[(*i)/2];
               Food_Position[NumberFood*2]=animaltype[*i];
               Food_Position[NumberFood*2 +1]=animaltype[*i+1];
               world[animaltype[*i]][animaltype[*i+1]]='F';
               NumberFood++;
           } 
        }
    }
    else if(direc=='w'){
        move_direction = 'w';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]-j][animaltype[*i+1]]=='-' ||world[animaltype[*i]-j][animaltype[*i+1]]=='H'||world[animaltype[*i]-j][animaltype[*i+1]]=='H'){
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
            printf("you can have only ((%d)) movementes along this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
                if(n*Energy > list[place].energy[(*i)/2]){
                    setTextColor(4,0);
                    printf("your energy isn't enough for this movement!!!\n");
                    printf("please decrease number of your movement\n");
                    setTextColor(11,0);
                }
            }while (n>j || n*Energy > list[place].energy[(*i)/2]);

            int EFood=SearchFood(animaltype[*i]-n,animaltype[*i+1]);
            if(world[animaltype[*i]-n][animaltype[*i+1]]=='-'){
               swap(world,animaltype[*i],animaltype[*i+1],animaltype[*i]-n,animaltype[*i+1]);
               animaltype[*i]-=n; 
            }
            else if(world[animaltype[*i]-n][animaltype[*i+1]]=='F'){
                world[animaltype[*i]][animaltype[*i+1]] = '-';
                world[animaltype[*i]-n][animaltype[*i+1]] = animal;
                list[place].energy[*i/2]+=Food_energy[EFood];
                Food_energy[EFood] = 0;
                animaltype[*i]-=n; 
            }
            else{
                winner = animal;
                sw=1;
                world[animaltype[*i]][animaltype[*i+1]]='-';
            }
            list[place].energy[(*i)/2]-=n*Energy;
            if(list[place].energy[(*i)/2]<Energy){
               SwforAnimal[(*i)/2]=1;
               Food_energy[NumberFood]=list[place].energy[(*i)/2];
               Food_Position[NumberFood*2]=animaltype[*i];
               Food_Position[NumberFood*2 +1]=animaltype[*i+1];
               world[animaltype[*i]][animaltype[*i+1]]='F';
               NumberFood++;
           } 
        }

    }
    else if(direc=='d'){
        move_direction = 'd';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]][animaltype[*i+1]+j]=='-' || world[animaltype[*i]][animaltype[*i+1]+j]=='H'|| world[animaltype[*i]][animaltype[*i+1]+j]=='F'){
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
            printf("you can have only ((%d)) movementes along this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
                if(n*Energy > list[place].energy[(*i)/2]){
                    setTextColor(4,0);
                    printf("your energy isn't enough for this movement!!!\n");
                    printf("please decrease number of your movement\n");
                    setTextColor(11,0);
                }
            }while (n>j || n*Energy > list[place].energy[(*i)/2]);

            int EFood=SearchFood(animaltype[*i],animaltype[*i+1]+n);
            if(world[animaltype[*i]][animaltype[*i+1]+n]=='-'){
               swap(world,animaltype[*i],animaltype[*i+1]+n,animaltype[*i],animaltype[*i+1]);
               animaltype[*i+1]+=n; 
            }
            else if(world[animaltype[*i]][animaltype[*i+1]+n]=='F'){
                world[animaltype[*i]][animaltype[*i+1]] = '-';
                world[animaltype[*i]][animaltype[*i+1]+n] = animal;
                list[place].energy[*i/2]+=Food_energy[EFood];
                Food_energy[EFood] = 0;
                animaltype[*i+1]+=n; 
            }
            else{
               winner = animal;
               sw=1;
               world[animaltype[*i]][animaltype[*i+1]]='-'; 
            }
            list[place].energy[(*i)/2]-=n*Energy;
           if(list[place].energy[(*i)/2]<Energy){
               SwforAnimal[(*i)/2]=1;
               Food_energy[NumberFood]=list[place].energy[(*i)/2];
               Food_Position[NumberFood*2]=animaltype[*i];
               Food_Position[NumberFood*2 +1]=animaltype[*i+1];
               world[animaltype[*i]][animaltype[*i+1]]='F';
               NumberFood++;
           } 
        }
    }
    else if(direc=='x'){
        move_direction = 'x';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]+j][animaltype[*i+1]]=='-' || world[animaltype[*i]+j][animaltype[*i+1]]=='H'|| world[animaltype[*i]+j][animaltype[*i+1]]=='F'){
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
            printf("you can have only ((%d)) movementes along this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
                if(n*Energy > list[place].energy[(*i)/2]){
                    setTextColor(4,0);
                    printf("your energy isn't enough for this movement!!!\n");
                    printf("please decrease number of your movement\n");
                    setTextColor(11,0);
                }
            }while (n>j || n*Energy > list[place].energy[(*i)/2]);

            int EFood=SearchFood(animaltype[*i]+n,animaltype[*i+1]);
            if(world[animaltype[*i]+n][animaltype[*i+1]]=='-'){
                swap(world,animaltype[*i]+n,animaltype[*i+1],animaltype[*i],animaltype[*i+1]);
                animaltype[*i]+=n;  
            }
            else if(world[animaltype[*i]+n][animaltype[*i+1]]=='F'){
                world[animaltype[*i]][animaltype[*i+1]] = '-';
                world[animaltype[*i]+n][animaltype[*i+1]] = animal;
                list[place].energy[*i/2]+=Food_energy[EFood];
                Food_energy[EFood] = 0;
                animaltype[*i]+=n;  
            }
            else{
                winner = animal;
                sw=1;
                world[animaltype[*i]][animaltype[*i+1]]='-';
            }
            list[place].energy[(*i)/2]-=n*Energy;
           if(list[place].energy[(*i)/2]<Energy){
               SwforAnimal[(*i)/2]=1;
               Food_energy[NumberFood]=list[place].energy[(*i)/2];
               Food_Position[NumberFood*2]=animaltype[*i];
               Food_Position[NumberFood*2 +1]=animaltype[*i+1];
               world[animaltype[*i]][animaltype[*i+1]]='F';
               NumberFood++;
           } 
        }
    }
    else if(direc=='q'){
        move_direction = 'q';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]-j][animaltype[*i+1]-j]=='-' || world[animaltype[*i]-j][animaltype[*i+1]-j]=='H'|| world[animaltype[*i]-j][animaltype[*i+1]-j]=='F'){
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
            printf("you can have only ((%d)) movementes along this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
                if(n*Energy > list[place].energy[*i/2]){
                    setTextColor(4,0);
                    printf("your energy isn't enough for this movement!!!\n");
                    printf("please decrease number of your movement\n");
                    setTextColor(11,0);
                }
            }while (n>j || n*Energy > list[place].energy[*i/2]);

            int EFood=SearchFood(animaltype[*i]-n,animaltype[*i+1]-n);
            if(world[animaltype[*i]-n][animaltype[*i+1]-n]=='-' ){
                swap(world,animaltype[*i]-n,animaltype[*i+1]-n,animaltype[*i],animaltype[*i+1]);
                animaltype[*i]-=n;
                animaltype[*i+1]-=n;  
            }
            else if(world[animaltype[*i]-n][animaltype[*i+1]-n]=='F'){
                world[animaltype[*i]][animaltype[*i+1]] = '-';
                world[animaltype[*i]-n][animaltype[*i+1]-n] = animal;
                list[place].energy[*i/2]+=Food_energy[EFood];
                Food_energy[EFood] = 0;
                animaltype[*i]-=n;
                animaltype[*i+1]-=n;  
            }
            else{
               winner = animal;
               sw=1;
               world[animaltype[*i]][animaltype[*i+1]]='-'; 
            }
            list[place].energy[*i/2]-=n*Energy;
           if(list[place].energy[*i/2]<Energy){
               SwforAnimal[*i/2]=1;
               Food_energy[NumberFood]=list[place].energy[*i/2];
               Food_Position[NumberFood*2]=animaltype[*i];
               Food_Position[NumberFood*2 +1]=animaltype[*i+1];
               world[animaltype[*i]][animaltype[*i+1]]='F';
               NumberFood++;
           } 
        }
    }
    else if(direc=='e'){
        move_direction = 'e';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]-j][animaltype[*i+1]+j]=='-' || world[animaltype[*i]-j][animaltype[*i+1]+j]=='H'|| world[animaltype[*i]-j][animaltype[*i+1]+j]=='F'){
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
           printf("you can have only ((%d)) movementes along this direction \n",j);
           do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
                if(n*Energy > list[place].energy[*i/2]){
                    setTextColor(4,0);
                    printf("your energy isn't enough for this movement!!!\n");
                    printf("please decrease number of your movement\n");
                    setTextColor(11,0);
                }
            }while (n>j || n*Energy > list[place].energy[*i/2]);

            int EFood=SearchFood(animaltype[*i]-n,animaltype[*i+1]+n);
           if(world[animaltype[*i]-n][animaltype[*i+1]+n]=='-'){
               swap(world,animaltype[*i]-n,animaltype[*i+1]+n,animaltype[*i],animaltype[*i+1]);
               animaltype[*i]-=n;
               animaltype[*i+1]+=n;
            }
            else if(world[animaltype[*i]-n][animaltype[*i+1]+n]=='F'){
                world[animaltype[*i]][animaltype[*i+1]] = '-';
                world[animaltype[*i]-n][animaltype[*i+1]+n] = animal;
                list[place].energy[*i/2]+=Food_energy[EFood];
                Food_energy[EFood] = 0;
               animaltype[*i]-=n;
               animaltype[*i+1]+=n;
            } 
           else{
              winner = animal;
              sw=1;
              world[animaltype[*i]][animaltype[*i+1]]='-'; 
           }
           list[place].energy[*i/2]-=n*Energy;
           if(list[place].energy[*i/2]<Energy){
               SwforAnimal[*i/2]=1;
               Food_energy[NumberFood]=list[place].energy[*i/2];
               Food_Position[NumberFood*2]=animaltype[*i];
               Food_Position[NumberFood*2 +1]=animaltype[*i+1];
               world[animaltype[*i]][animaltype[*i+1]]='F';
               NumberFood++;
           } 
        }
    }
    else if(direc=='c'){
        move_direction = 'c';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]+j][animaltype[*i+1]+j]=='-' || world[animaltype[*i]+j][animaltype[*i+1]+j]=='H'|| world[animaltype[*i]+j][animaltype[*i+1]+j]=='F'){
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
            printf("you can have only ((%d)) movementes along this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
                if(n*Energy > list[place].energy[*i/2]){
                    setTextColor(4,0);
                    printf("your energy isn't enough for this movement!!!\n");
                    printf("please decrease number of your movement\n");
                    setTextColor(11,0);
                }
            }while (n>j || n*Energy > list[place].energy[*i/2]);

            int EFood=SearchFood(animaltype[*i]+n,animaltype[*i+1]+n);
            if(world[animaltype[*i]+n][animaltype[*i+1]+n]=='-'){
                swap(world,animaltype[*i]+n,animaltype[*i+1]+n,animaltype[*i],animaltype[*i+1]);
                animaltype[*i]+=n;
                animaltype[*i+1]+=n;
            }
            else if(world[animaltype[*i]+n][animaltype[*i+1]+n]=='F'){
                world[animaltype[*i]][animaltype[*i+1]] = '-';
                world[animaltype[*i]+n][animaltype[*i+1]+n] = animal;
                list[place].energy[*i/2]+=Food_energy[EFood];
                Food_energy[EFood] = 0;
                animaltype[*i]+=n;
                animaltype[*i+1]+=n;
            }
            else{
               winner = animal;
               sw=1;
               world[animaltype[*i]][animaltype[*i+1]]='-'; 
            }
            list[place].energy[*i/2]-=n*Energy;
           if(list[place].energy[*i/2]<Energy){
               SwforAnimal[*i/2]=1;
               Food_energy[NumberFood]=list[place].energy[*i/2];
               Food_Position[NumberFood*2]=animaltype[*i];
               Food_Position[NumberFood*2 +1]=animaltype[*i+1];
               world[animaltype[*i]][animaltype[*i+1]]='F';
               NumberFood++;
           } 
        }
    }
    else if(direc=='z'){
        move_direction = 'z';
        int j=1;
        while(j<=n){
            if(world[animaltype[*i]+j][animaltype[*i+1]-j]=='-' || world[animaltype[*i]+j][animaltype[*i+1]-j]=='H' || world[animaltype[*i]+j][animaltype[*i+1]-j]=='H'){
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
            printf("you can have only ((%d)) movementes along this direction \n",j);
            do{
                printf("Please enter the number of movements you want:(1 to %d)\n",j);
                scanf("%d",&n);
                if(n*Energy > list[place].energy[*i/2]){
                    setTextColor(4,0);
                    printf("your energy isn't enough for this movement!!!\n");
                    printf("please decrease number of your movement\n");
                    setTextColor(11,0);
                }
            }while (n>j || n*Energy > list[place].energy[*i/2]);

            int EFood=SearchFood(animaltype[*i]+n,animaltype[*i+1]-n);
            if(world[animaltype[*i]+n][animaltype[*i+1]-n]=='-'){
               swap(world,animaltype[*i]+n,animaltype[*i+1]-n,animaltype[*i],animaltype[*i+1]);
               animaltype[*i]+=1;
               animaltype[*i+1]-=1; 
            }
            else if(world[animaltype[*i]+n][animaltype[*i+1]-n]=='F'){
                world[animaltype[*i]][animaltype[*i+1]] = '-';
                world[animaltype[*i]+n][animaltype[*i+1]-n] = animal;
                list[place].energy[*i/2]+=Food_energy[EFood];
                Food_energy[EFood] = 0;
                animaltype[*i]+=1;
                animaltype[*i+1]-=1; 
            }
            else{
               winner = animal;
               sw=1;
               world[animaltype[*i]][animaltype[*i+1]]='-'; 
            }
            list[place].energy[*i/2]-=n*Energy;
           if(list[place].energy[*i/2]<Energy){
               SwforAnimal[*i/2]=1;
               Food_energy[NumberFood]=list[place].energy[*i/2];
               Food_Position[NumberFood*2]=animaltype[*i];
               Food_Position[NumberFood*2 +1]=animaltype[*i+1];
               world[animaltype[*i]][animaltype[*i+1]]='F';
               NumberFood++;
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

void moveunc(int j , int animal_place){
    int x = noncanimals[j];
    int y = noncanimals[j+1];
    list[animal_place].energy[j/2] -= list[animal_place].movemente;
    if(list[animal_place].energy[(j)/2]<list[animal_place].movemente){
        SwforAnimal[(j)/2]=1;
        Food_energy[NumberFood]=list[animal_place].energy[(j)/2];
        Food_Position[NumberFood*2]=noncanimals[j];
        Food_Position[NumberFood*2 +1]=noncanimals[j+1];
        world[noncanimals[j]][noncanimals[j+1]]='F';
        NumberFood++;
        return;
    }
    if(x>unc[0]){
        if(y>unc[1]){
            if(world[x-1][y-1] == '-' || world[x-1][y-1] == 'H'|| world[x-1][y-1] == 'F')while(movements<unc_possible_move && sw == 0) movewithkey(noncanimals , 'q' , &j), movements++;
            else if (world[x-1][y] == '-'|| world[x-1][y] == 'H' || world[x-1][y] == 'F') while(movements<unc_possible_move)movewithkey(noncanimals , 'a' , &j), movements++;
            else if ((world[x][y-1] == '-'|| world[x][y-1] == 'H'|| world[x][y-1] == 'F')) while(movements<unc_possible_move)movewithkey(noncanimals , 'x' , &j), movements++;
        }
        if(y<unc[1]){
            if(world[x-1][y+1] == '-'|| world[x-1][y+1] == 'H'|| world[x-1][y+1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'e' , &j), movements++;
            else if(world[x][y+1] == '-'|| world[x][y+1] == 'H'|| world[x][y+1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'd' , &j), movements++;
            else if(world[x-1][y] == '-'|| world[x-1][y] == 'H'|| world[x-1][y] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'w' , &j), movements++;
        }
        if(y==unc[1]){
            if(world[x-1][y] == '-'|| world[x-1][y] == 'H'|| world[x-1][y] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'w' , &j), movements++;
            else if(world[x-1][y+1]=='-'|| world[x-1][y+1] == 'H'|| world[x-1][y+1] == 'F') while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'e' , &j), movements++;
            else if(world[x+1][y+1]=='-'|| world[x+1][y+1] == 'H'|| world[x+1][y+1] == 'F') while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'c' , &j), movements++;
        }
    }
    if(x<unc[0]){
        if(y>unc[1]){
            if(world[x+1][y-1] == '-'|| world[x+1][y-1] == 'H'|| world[x+1][y-1] == 'F' )while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'z' , &j), movements++;
            else if(world[x+1][y] == '-'|| world[x+1][y] == 'H'|| world[x+1][y] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'x' , &j), movements++;
            else if(world[x][y-1] == '-'|| world[x][y-1] == 'H'|| world[x][y-1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'a' , &j), movements++;
        }
        if(y<unc[1]){
            if(world[x+1][y+1] == '-'|| world[x+1][y+1] == 'H'|| world[x+1][y+1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'c' , &j), movements++;
            else if(world[x+1][y] == '-'|| world[x+1][y] == 'H'|| world[x+1][y] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'x' , &j), movements++;
            else if(world[x][y+1] == '-'|| world[x][y+1] == 'H'|| world[x][y+1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'd' , &j), movements++;
        }
        if(y==unc[1]){
            if(world[x+1][y] == '-'|| world[x+1][y] == 'H'|| world[x+1][y] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'x' , &j), movements++;
            else if(world[x+1][y-1] == '-'|| world[x+1][y-1] == 'H'|| world[x+1][y-1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'z' , &j), movements++;
            else if(world[x+1][y+1] == '-'|| world[x+1][y+1] == 'H'|| world[x+1][y+1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'c' , &j), movements++;
        }
    }
    if(x==unc[0]){
        if(y>unc[1]){
            if(world[x][y-1] == '-'|| world[x][y-1] == 'H'|| world[x][y-1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'a' , &j), movements++;
            else if(world[x-1][y-1] == '-'|| world[x-1][y-1] == 'H'|| world[x-1][y-1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'q' , &j), movements++;
            else if(world[x+1][y-1] == '-'|| world[x+1][y-1] == 'H'|| world[x+1][y-1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'z' , &j), movements++;
        }
        if(y<unc[1]){
            if(world[x][y+1] == '-'|| world[x][y+1] == 'H'|| world[x][y+1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'd' , &j), movements++;
            else if(world[x-1][y+1]=='-'|| world[x-1][y+1] == 'H'|| world[x-1][y+1] == 'F') while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'e' , &j) , movements++;
            else if(world[x+1][y+1] == '-'|| world[x+1][y+1] == 'H'|| world[x+1][y+1] == 'F')while(movements<unc_possible_move&& sw == 0)movewithkey(noncanimals , 'c' , &j) , movements++;
        }
    }

    
    
}

int main(){

    FILE *log;
    log = fopen("C:\\Team_7_Final_Project\\game-log.txt" , "wt");
    rewind(log);
    fprintf(log , "salam dadash");
    FILE *readfile;
    int c[2];

    readfile = fopen("C:\\Team_7_Final_Project\\map-phase1.txt" , "rt" );
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


    setTextColor(11,0);
    int n=0;
    int number = 0;
    printf("\n");
    printf("The Creature under your control : %c\n",controlanimal);
    printf("MOVE with:\n");
    printf("          q -- w -- e\n");
    printf("          |    |    |\n");
    printf("          a -- @ -- d\n");
    printf("          |    |    |\n");
    printf("          z -- x -- c\n");



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

            if(world[i][j] != controlanimal && world[i][j] != 'H' && world[i][j] != '#' && world[i][j] != '-' && world[i][j] != 'F'){
                noncanimals[number]=i;
                noncanimals[number+1]=j;
                number+=2;
            }
        }
    }

    int place=search(list,controlanimal); //getting place of controlled creature in array "list".

    while(sw==0){
        int i = 0;
        while(i<n && sw ==0){
            if(SwforAnimal[i/2]==0){
                animal = controlanimal;

                //system("cls");
                printf("you are at position:(%d,%d) energy(%d)\n",panimal[i],panimal[i+1] , list[place].energy[i/2]);
                int x1 = panimal[i];
                int y1 = panimal[i+1];
                mapprinter(world,size,x1,y1);
                moving_creature = world[x1][y1];
                printf("please enter direction of your movement:\n");
                scanf(" %c" , &direc);
                movewithkey2( place , panimal , direc , &i , controlanimal);
                if(moved == 1){
                    fprintf(log , "moving creature %c in (%d,%d) into %c direction\n" , moving_creature, x1 , y1 , move_direction );
                }
                if(sw==1) {
                    printf("gg , wp all -> creature %c won!!!",winner);
                    fprintf( log, "gg , wp all -> creature %c won!!!",winner);
                }
            }
            else{
                i+=2;
            }
        }   
        int j = 0;
        while(j<number && sw ==0){
            movements = 0;
            theNearest(noncanimals[j] , noncanimals[j+1] , 'H');
            int x = noncanimals[j];
            int y = noncanimals[j+1];
            animal = world[x][y];
            int animal_place=search(list,animal);
            unc_possible_move = list[animal_place].numberm;
            printf("moving creature %c in position(%d,%d) to (%d,%d) : energy(%d)\n" , world[x][y] ,x , y , unc[0] , unc[1] , list[animal_place].energy[j/2]);
            mapprinter(world,size,x,y);
            moveunc(j , animal_place);
            fprintf(log , "moving creature %c in (%d,%d) into %c direction\n" , animal ,x , y , move_direction );
            sleep(2000);
            //system("cls");
            j += 2;
            if(sw==1){
                printf("gg , wp all -> creature %c won!!!",winner);
                fprintf( log, "gg , wp all -> creature %c won!!!",winner);
            }

        }
    
    
    
    
    
    
    
    }
    fclose(log);
    printf("\nPress Any Key To Exit");
    getch();


    
}
