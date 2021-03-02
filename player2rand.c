#include <stdio.h>
#include <stdlib.h>

void player2(int ground[12][12], int *strategy_x, int *strategy_y){
    *strategy_x=rand()%10+1;
    *strategy_y=rand()%10+1;
}