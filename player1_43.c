#include <stdio.h>
#include <stdlib.h>

#define Me 1
#define Enemy 2

void player1(int ground[12][12], int *strategy_x, int *strategy_y){
    


    *strategy_x=rand()%10+1;
    *strategy_y=rand()%10+1;
}

int player2_atk_w[12][12];
int player2_def_w[12][12];
void player2_eval(int ground[12][12],int depth){
    for (int i = 1; i <= 10;i++){
        for (int j = 1; j <= 10;j++){
            if(ground[i][j]!=0){
                player2_atk_w[i][j] = -100;
            }else{
                for (int d = 1; d <= depth; d++){
                    if(i+d<=11&&i-d>=0){
                        if (ground[i + d][j] == 0){
                            player2_atk_w[i][j] += 1;
                        }
                        if (ground[i + d][j] == Me){
                            player2_atk_w[i][j] += 5;
                        }
                        if (ground[i + d][j] == Enemy){
                            player2_atk_w[i][j] -= 5;
                        }
                    }
                }
            }
        }
    }
}