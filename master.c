/*
 * gomoku.c
 *
 *  Created on: 2017/06/30
 *      Author: b1016112 Daichi Matsumoto
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GROUND_X 12
#define GROUND_Y 12
#define P1  1
#define P2  2
#define win 5

#define DEBUG

int judge(int p, int ground[GROUND_Y][GROUND_X]){
	int judge = 0;
	int sum=0;
	int i,j,k;

	for(i=1;i<GROUND_Y-1;i++){
		for(j=1;j<GROUND_X-1;j++){
			if(ground[i][j] == p) sum++;
			else sum=0;
			if(sum==win)judge=1;
			else if(sum>win)judge=0;
		}
		sum=0;
	}
	for(i=1;i<GROUND_X-1;i++){
		for(j=1;j<GROUND_Y-1;j++){
			if(ground[j][i] == p) sum++;
			else sum=0;
			if(sum==win)judge=1;
			else if(sum>win)judge=0;
		}
		sum=0;
	}

	for(j=1;j<GROUND_Y-1;j++){
		for( i=1, k=j ; (i<GROUND_X-1, k<GROUND_Y-1) ; i++, k++){
			if(ground[k][i] == p) sum++;
			else sum=0;
			if(sum==win)judge=1;
			else if(sum>win)judge=0;
		}
		sum=0;
	}

	for(j=1;j<GROUND_X-1;j++){
		for( i=j, k=1 ; (i<GROUND_X-1, k<GROUND_Y-1) ; i++, k++){
			if(ground[k][i] == p) sum++;
			else sum=0;
			if(sum==win)judge=1;
			else if(sum>win)judge=0;
		}
		sum=0;
	}

	for(j=GROUND_X-2;j>0;j--){
		for( i=j, k=1 ; i>0, k<GROUND_Y-1 ; i--, k++){
			if(ground[k][i] == p) sum++;
			else sum=0;
			if(sum==win)judge=1;
			else if(sum>win)judge=0;
		}
		sum=0;
	}

	for(j=1;j<GROUND_Y-1;j++){
		for( i=GROUND_X-2, k=j ; (i>0, k<GROUND_Y-1) ; i--, k++){
			if(ground[k][i] == p) sum++;
			else sum=0;
			if(sum==win)judge=1;
			else if(sum>win)judge=0;
		}
		sum=0;
	}

	for(i=1;i<GROUND_Y-1;i++){
		for(j=1;j<GROUND_X-1;j++){
			if(ground[i][j] == 0) sum++;
		}
	}
	if(sum==0)judge=2;
	return judge;
}


void player_exchange(int *player){
	switch(*player){
	case P1:
		*player = P2;
		break;
	case P2:
		*player = P1;
		break;
	}
}

void prot(int *player, int ground[GROUND_Y][GROUND_X] ,int *s,int *t){
	if(ground[*t][*s] !=0){
		printf("Already put\n");
		player_exchange(player);
	}else if(ground[*t][*s] == 0){
		if(*player == P1) ground[*t][*s] = 1;
		else if (*player == P2) ground[*t][*s] = 2;
	}
#ifdef DEBUG
	for(int i=0;i<GROUND_Y;i++){
		for(int j=0;j<GROUND_X;j++){
			if(ground[i][j]==1) printf("  O  ");
			else if(ground[i][j]==2) printf("  X  ");
			else if(ground[i][j]==-1){
				if((i==0&&j==0)||(i==0&&j==GROUND_X-1)||(i==GROUND_Y-1&&j==0)||(i==GROUND_Y-1&&j==GROUND_X-1)) printf(" ### ");
				else if(i==0||i==GROUND_Y-1) printf(" #%2d ",j);
				else if(j==0||j==GROUND_X-1) printf(" #%2d ",i);

			}
			else printf("  -  ");
		}
		printf("\n");

	}
#endif
}

void Initiarize(int ground[GROUND_Y][GROUND_X]){
	for(int i=0;i<GROUND_Y;i++){
		for(int j=0;j<GROUND_X;j++){
			if(j==0 || i==0 || i== GROUND_Y-1 || j==GROUND_X-1) ground[i][j]= -1;
			else ground[i][j]=0;
		}
	}
    ground[5][5]=1;
    ground[6][6]=1;
    ground[5][6]=2;
    ground[6][5]=2;
}

void Result(int ground[GROUND_Y][GROUND_X]){
    for(int i=0;i<GROUND_Y;i++){
		for(int j=0;j<GROUND_X;j++){
			if(ground[i][j]==1) printf("  O  ");
			else if(ground[i][j]==2) printf("  X  ");
			else if(ground[i][j]==-1){
				if((i==0&&j==0)||(i==0&&j==GROUND_X-1)||(i==GROUND_Y-1&&j==0)||(i==GROUND_Y-1&&j==GROUND_X-1)) printf(" ### ");
				else if(i==0||i==GROUND_Y-1) printf(" #%2d ",j);
				else if(j==0||j==GROUND_X-1) printf(" #%2d ",i);

			}
			else printf("  -  ");
		}
		printf("\n");

	}
}


void Finish(int stat,int *player){
	if(stat==1){
        switch(*player){
            case P1:
                printf("player%d(O) WIN\n",*player);
                break;
            case P2:
                printf("player%d(X) WIN\n",*player);
                break;
            }
    }
	if(stat==2) printf("DRAW!\n");
}

int main(void){

	int s,t;
	int ground[GROUND_Y][GROUND_X];
	int player = P1;
    int P1Strategy_x,P1Strategy_y;
    int P2Strategy_x,P2Strategy_y;

	Initiarize(ground);

    srand((unsigned) time(NULL));

	TOP:
	switch(player){
	case P1:
        player1(ground,&P1Strategy_x,&P1Strategy_y);
#ifdef DEBUG
        printf("Player1(O):x=%d,y=%d\n",P1Strategy_x,P1Strategy_y);
#endif
        prot(&player,ground,&P1Strategy_x,&P1Strategy_y);
	    break;
	case P2:
		//printf("CPU\n");
		player2(ground,&P2Strategy_x,&P2Strategy_y);
#ifdef DEBUG
        printf("Player2(X):x=%d,y=%d\n",P2Strategy_x,P2Strategy_y);
#endif
        prot(&player,ground,&P2Strategy_x,&P2Strategy_y);
		break;
	}
	if(judge(player,ground) == 1||judge(player,ground) == 2) {
#ifndef DEBUG
        Result(ground);
#endif
        Finish(judge(player,ground),&player);

        goto EXITLOOP;
    }
	player_exchange(&player);
	goto TOP;
    EXITLOOP:;
	return 0;
}
