#include "beggar.h"
#include <stdio.h>
#include <stdlib.h>
int main(){
    int i;
    for (i = 2; i <= 10; i++){
        stats s = statistics(i, 100);
        stats *p = &s;
        printf("--------------- Players: %d ---------------\n", i);
        printf("Shortest Game: %d turns\n",  p->shortest);
        printf("Longest Game: %d turns\n",  p->longest);
        printf("Average Game Length: %f turns\n",  p->average);
        printf("-------------------------------------------\n");
        printf("\n");
    }
}