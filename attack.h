int SwforCheck[8]={0};

int Check(char world[][20],char animal,int x1,int y1,int *i,char *ch,int *x2,int *y2){

    if(SwforCheck[0]==0){

        if(world[x1][y1+1]!=animal && world[x1][y1+1]!='-' && world[x1][y1+1]!='#' && world[x1][y1+1]!='F' && world[x1][y1+1]!='H'){
            SwforCheck[0]=1;
            *i+=1;
            *ch=world[x1][y1+1];
            *x2=x1;
            *y2=y1+1;
            return 1;
        }
        else{
            SwforCheck[0]=1;
            *i+=1;
        }
    }
    if(SwforCheck[1]==0){

        if(world[x1-1][y1+1]!=animal && world[x1-1][y1+1]!='-' && world[x1-1][y1+1]!='#' && world[x1-1][y1+1]!='F' && world[x1-1][y1+1]!='H'){
            SwforCheck[1]=1;
            *i+=1;
            *ch=world[x1-1][y1+1];
            *x2=x1-1;
            *y2=y1+1;
            return 1;
        }
        else{
            SwforCheck[1]=1;
            *i+=1;
        }
    }
    if(SwforCheck[2]==0){

        if(world[x1-1][y1]!=animal && world[x1-1][y1]!='-' && world[x1-1][y1]!='#' && world[x1-1][y1]!='F' && world[x1-1][y1]!='H'){
            SwforCheck[2]=1;
            *i+=1;
            *ch=world[x1-1][y1];
            *x2=x1-1;
            *y2=y1;
            return 1;
        }
        else{
            SwforCheck[2]=1;
            *i+=1;
        }
    }
    if(SwforCheck[3]==0){

        if(world[x1-1][y1-1]!=animal && world[x1-1][y1-1]!='-' && world[x1-1][y1-1]!='#' && world[x1-1][y1-1]!='F' && world[x1-1][y1-1]!='H'){
            SwforCheck[3]=1;
            *i+=1;
            *ch=world[x1-1][y1-1];
            *x2=x1-1;
            *y2=y1-1;
            return 1;
        }
        else{
            SwforCheck[3]=1;
            *i+=1;
        }
    }
    if(SwforCheck[4]==0){

        if(world[x1][y1-1]!=animal && world[x1][y1-1]!='-' && world[x1][y1-1]!='#' && world[x1][y1-1]!='F' && world[x1][y1-1]!='H'){
            SwforCheck[4]=1;
            *i+=1;
            *ch=world[x1][y1-1];
            *x2=x1;
            *y2=y1-1;
            return 1;
        }
        else{
            SwforCheck[4]=1;
            *i+=1;
        }
    }
    if(SwforCheck[5]==0){

        if(world[x1+1][y1-1]!=animal && world[x1+1][y1-1]!='-' && world[x1+1][y1-1]!='#' && world[x1+1][y1-1]!='F' && world[x1+1][y1-1]!='H'){
            SwforCheck[5]=1;
            *i+=1;
            *ch=world[x1+1][y1-1];
            *x2=x1+1;
            *y2=y1-1;
            return 1;
        }
        else{
            SwforCheck[5]=1;
            *i+=1;
        }
    }
    if(SwforCheck[6]==0){

        if(world[x1+1][y1]!=animal && world[x1+1][y1]!='-' && world[x1+1][y1]!='#' && world[x1+1][y1]!='F' && world[x1+1][y1]!='H'){
            SwforCheck[6]=1;
            *i+=1;
            *ch=world[x1+1][y1];
            *x2=x1+1;
            *y2=y1;
            return 1;
        }
        else{
            SwforCheck[6]=1;
            *i+=1;
        }
    }
    if(SwforCheck[7]==0){

        if(world[x1+1][y1+1]!=animal && world[x1+1][y1+1]!='-' && world[x1+1][y1+1]!='#' && world[x1+1][y1+1]!='F' && world[x1+1][y1+1]!='H'){
            SwforCheck[7]=1;
            *i+=1;
            *ch=world[x1+1][y1+1];
            *x2=x1+1;
            *y2=y1+1;
            return 1;
        }
        else{
            SwforCheck[7]=1;
            *i+=1;
        }
    }
    return 0;
}