#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define row 3
#define column 3
/*initialize the array*/
void INchess(char chess[3][3],int a , int b)
{
    int r=0,c=0;
    for (;r<a;r++)
    {
        for(c=0;c<b;c++)
        {
            chess[r][c]=' ';
        }
    }
}



void printchess(char chess[3][3])
{
    int c=0;
    for (;c<2;c++)
    {
        printf("    %c|%c  |%c    ",chess[c][0],chess[c][1],chess[c][2]);
        printf("\n");
        printf("  ---|---|---   ");
        printf("\n");
    }
    printf("    %c|%c  |%c    ",chess[2][0],chess[2][1],chess[2][2]);
    printf("\n");
}


void playermove(char chess[3][3],int a,int b,char ch)
{
    chess[a-1][b-1]=ch;
}


int judgeplace (char chess[3][3],int a,int b)
{
    if (chess[a-1][b-1] ==' ')
        return 1;
    else
        return 0;
}


int judgefull(char chess[3][3])
{
    if (chess[0][0]!=' ' &&chess[0][1]!=' ' &&chess[0][2]!=' ' &&chess[1][0]!=' ' &&chess[1][1]!=' ' &&chess[1][2]!=' ' &&chess[2][0]!=' ' &&chess[2][1]!=' ' &&chess[2][2]!=' ' )
        return 1;
    else
        return 0;
}


int judgewin(char c[3][3],char ch)
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

int minimax(char chess[3][3],int depth,int player)
{
    int score=judgewin(chess,'^');
    if (score!=0)
    {
        return score;
    }
    else
    {
        if (score==0)
        {
            if(player)
            {
                int maxscore=-10000;
                for (int i=1;i<4;i++)
                {
                    for (int j=1;j<4;j++)
                    {
                        if (judgeplace(chess, i, j)==1)
                        {
                            playermove(chess, i, j,'^');
                            int currentscore=minimax(chess,depth+1,!player);
                            chess[i-1][j-1]=' ';
                            if (currentscore>maxscore)
                                maxscore=currentscore;
                        }
                    }
                }
                return maxscore;
            }
            else
            {
                int minscore=10000;
                for (int i=1;i<4;i++)
                {
                    for (int j=1;j<4;j++)
                    {
                        if (judgeplace(chess, i, j)==1)
                            playermove(chess, i, j,'#');
                        int currentscore=minimax(chess, depth+1, !player);
                        chess[i-1][j-1]=' ';
                        if (currentscore<minscore)
                        {
                            minscore=currentscore;
                        }
                    }
                }
                return score;
            }
        }
        else
            return score;
    }
}


void minimax_move(char chess[3][3])
{
    int maxscore=-10000;
    int besta=-1;
    int bestb=-1;
    for(int i=1;i<4;i++)
    {
        for (int j=1;j<4;j++)
        {
            if (judgeplace(chess, i, j)==1)
            {
                playermove(chess, i, j,'^');
                int currentscore=minimax(chess,0,0);
                chess[i-1][j-1]=' ';
                if (currentscore>maxscore)
                {
                    maxscore=currentscore;
                    besta=i;
                    bestb=j;
                }
            }
        }
    }
    playermove(chess, besta, bestb,'^');
}


int main (void)
{
      char chess[3][3]={0};
    INchess(chess,row,column);
    printchess(chess);
    int mode =0;
    int a,b,c,d;
    do
    {
        printf("nice to see u ,player \n");
        printf("in u turn to move please input the row and column u wanna move \n");
        printf("mode choose :   AI(1)        LOCAL BATTLE(2)\n");
        scanf("%d",&mode);
    }while (mode !=1 && mode!= 2);
    if (mode ==2)
    {
        for (a=0,b=0,c=0,d=0;;)
        {
            printf("player1(#) move please:");
            scanf("%d%d",&a,&b);
            if (a>3 || b>3 || a<1 || b<1)
            {
                printf("number u input must less than 3 and bigger than 0");
                for (;a>3 || b>3 || a<1 || b<1;)
                {
                    printf("number u input must less than 3 and bigger than 0\n");
                    printf("player1(#)move again:");
                    scanf("%d%d",&a,&b);
                }
            }
            if (judgeplace(chess,a,b)==0)
            {
                do {
                    printf("this move is against the rule ,move again\n");
                    printf("player1(#) move please:");
                    scanf("%d%d",&a,&b);
                } while (judgeplace(chess, a, b)==0);
                playermove(chess,a,b,'#');
                printchess(chess);
            }
            else
            {
                playermove(chess,a,b,'#');
                printchess(chess);
            }
            if(judgefull(chess)==1)
            {
                printf("game over!!!");
                if(judgewin(chess,'#')==1)
                {
                    printf("player1 win**********\n");
                    printf("game over ***********\n");
                    break;
                }

                break;
            }
            if(judgewin(chess,'#')==1)
            {
                printf("player1 win**********\n");
                printf("game over ***********\n");
                break;
            }
            printf("player2(^) move please:");
            scanf("%d%d",&c,&d);
            if (c>3 || d>3 || c<1 || d<1)
            {
                for (;c>3 || d>3 || c<1 || d<1;)
                {
                    printf("number u input must less than 3 and bigger than 0\n");
                    printf("player2(^)move again:");
                    scanf("%d%d",&c,&d);
                }
            }
            if (judgeplace(chess,c,d)==0)
            {
                do {
                    printf("this move is against the rule ,move again\n");
                    printf("player2(^) move please:");
                    scanf("%d%d",&c,&d);
                } while (judgeplace(chess, c, d)==0);
                playermove(chess,c,d,'^');
                printchess(chess);
            } else
            {
                playermove(chess,c,d,'^');
                printchess(chess);
            }
            if(judgefull(chess)==1)
            {
                printf("game over!!!");
                if(judgewin(chess,'^')==1)
                {
                    printf("player2 win**********\n");
                    printf("game over ***********\n");
                    break;
                }
                break;
            }
            if(judgewin(chess,'^')==1)
            {
                printf("player2 win**********\n");
                printf("game over ***********\n");
                break;
            }
           }
    }
    
    if (mode==1)
    {
        for (a=0,b=0;;)
        {
            printf("player(#) move please:");
            scanf("%d%d",&a,&b);
            if (a>3 || b>3 || a<1 || b<1)
            {
                printf("number u input must less than 3 and bigger than 0");
                for (;a>3 || b>3 || a<1 || b<1;)
                {
                    printf("number u input must less than 3 and bigger than 0\n");
                    printf("player(#)move again:");
                    scanf("%d%d",&a,&b);
                }
            }
            if (judgeplace(chess,a,b)==0)
            {
                do {
                    printf("this move is against the rule ,move again\n");
                    printf("player(#) move please:");
                    scanf("%d%d",&a,&b);
                } while (judgeplace(chess, a, b)==0);
                playermove(chess,a,b,'#');
                printchess(chess);
            }
            else
            {
                playermove(chess,a,b,'#');
                printchess(chess);
            }
            if(judgefull(chess)==1)
            {
                printf("game over!!!");
                if(judgewin(chess,'#')==1)
                {
                    printf("player win**********\n");
                    printf("game over ***********\n");
                    break;
                }
                
                break;
            }
            if(judgewin(chess,'#')==1)
            {
                printf("player win**********\n");
                printf("game over ***********\n");
                break;
            }
            
            minimax_move(chess);
            printchess(chess);
            if(judgefull(chess)==1)
            {
                printf("game over!!!");
                if(judgewin(chess,'^')==1)
                {
                    printf("AI win**********\n");
                    printf("game over ***********\n");
                    break;
                }
                
                break;
            }
            if(judgewin(chess,'^')==1)
            {
                printf("AI win**********\n");
                printf("game over ***********\n");
                break;
            }

        }
        
    }
    return 0;
}
