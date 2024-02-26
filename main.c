#include <stdio.h>
#include <stdlib.h>
//initialize the chess board
void inchess(char chess[3][3])
{
    int m,n;
    for (m=0;m<3;m++)
    {
        for (n=0;n<3;n++)
        {
            chess[m][n]=' ';
        }
    }
}

//print the present chess board
void printchess(char chess[3][3])
{
    printf("                      %c | %c  | %c \n",chess[0][0],chess[0][1],chess[0][2]);
    printf("                     ---|----|---\n");
    printf("                      %c | %c  | %c \n",chess[1][0],chess[1][1],chess[1][2]);
    printf("                     ---|----|---\n");
    printf("                      %c | %c  | %c \n",chess[2][0],chess[2][1],chess[2][2]);
}


//get the current score
int reslut(char c[3][3],char ch)
{
    if(c[0][0]==ch && c[0][1]==ch && c[0][2]==ch )
        return 1;
    if(c[1][0]==ch && c[1][1]==ch && c[1][2]==ch )
        return 1;
    if(c[2][0]==ch && c[2][1]==ch && c[2][2]==ch )
        return 1;
    if(c[0][0]==ch && c[1][0]==ch && c[2][0]==ch)
        return 1;
    if(c[0][1]==ch && c[1][1]==ch && c[2][1]==ch)
        return 1;
    if(c[0][2]==ch && c[1][2]==ch && c[2][2]==ch)
            return 1;
    if(c[0][0]==ch && c[1][1]==ch && c[2][2]==ch)
        return 1;
    if(c[0][2]==ch && c[1][1]==ch && c[2][0]==ch)
        return 1;
    else
        return 0;
}

int judgeplace(char chess[3][3],int a,int b)
{
    if (chess[a][b]==' ')
        return 1;
    else
        return 0;
}
//cosidering draw and show that in the score funciton
int checkfull(char chess[3][3])
{
    int a,b;
    int t=0;
    for (a=0;a<3;a++)
    {
        for (b=0;b<3;b++)
        {
            if (chess[a][b]!=' ')
            {
                t++;
                return t;
            }
        }
    }
    return t;
}

int score(char chess[3][3])
{
    //draw
    if (checkfull(chess)==1&&reslut(chess,'#')==0&&reslut(chess,'^')==0)
        return 0;
    else
    {
        //AI goals
        if (reslut(chess,'#')==1)
            return -1;
        else
        {
            //player goals
            if (reslut(chess,'^')==1)
                return 1;
            //game continues
            else
                return 0;
        }
    }
}


//put the chess player wanna
void playerputchess(char chess[3][3],int a,int b)
{
    chess[a][b]='#';
}


//caution:depth to 0 the minimax resurse will stop
int minimax(char chess[3][3],int depth,int player)
{
    if (depth==0)
        return score(chess);
    
    else
    {
        int currentscore=0;
        if (score(chess)!=0)
            return score(chess);
        //the main part of minimax
        else
        {
            int a,b;
            //the AI turn
            if(player)
            {
                int maxscore=-10;
                for (a=0;a<3;a++)
                {
                    for (b=0;b<3;b++)
                    {
                        if (judgeplace(chess, a, b)==1)
                        {
                            chess[a][b]='^';
                            currentscore=minimax(chess,depth-1,!player);
                            chess[a][b]=' ';
                            if (currentscore>maxscore)
                                maxscore=currentscore;
                        }
                    }
                }
                return maxscore;
            }
            //the player turn
            else
            {
                int minscore=10;
                
                for (a=0;a<3;a++)
                {
                    for (b=0;b<3;b++)
                    {
                        if (judgeplace(chess, a, b)==1)
                        {
                            playerputchess(chess,a,b);
                            currentscore=minimax(chess,depth-1,!player);
                            chess[a][b]=' ';
                            if (currentscore<minscore)
                                minscore=currentscore;
                        }
                    }
                }
                return minscore;
            }
        }
        //below is the main part of minimax
    }
}
    
    
void AImove (char chess[3][3],int depth)
{
    int besta =0,bestb =0;
    int bestscore=-10;
    int currentscore;
    int a,b;
    for (a=0;a<3;a++)
    {
        for (b=0;b<3;b++)
        {
            if (judgeplace(chess, a, b)==1)
            {
                chess[a][b]='^';
                currentscore=minimax(chess,depth,0);
                chess[a][b]=' ';
                if (bestscore<currentscore)
                {
                    bestscore=currentscore;
                    besta=a;
                    bestb=b;
                }
            }
        }
    }
    chess[besta][bestb]='^';
}



int main(void)
{
    char chess[3][3]={0};
    inchess(chess);
    printf("***********************hello player i am tic tac toe bot,below is the chess board:******************************\n");
    printchess(chess);
    int a=0,b=0;
    int depth=8;
    while (1)
    {
        if (score(chess)!=0)
        {
            printf("***********************          game over       ******************************\n");
            break;
        }
        printf("the place u wanna :");
        scanf("%d%d",&a,&b);
        playerputchess(chess,a-1,b-1);
        depth--;
        AImove(chess,depth);
        printchess(chess);
        depth--;
    }
    return 0;
}

