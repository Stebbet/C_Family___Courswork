
#include <stdio.h>
#include "riffle.h"
#include <time.h>
#include <stdlib.h>


int main(){
    int i;

    // Initialize the random number generator
    time_t t;
    srand((unsigned) time(&t));

    for (i = 0; i <= 15; i++) {
        float q = average_quality(50, i, 30);
        printf("num shuffles: %2d - quality: %f\n", i, q);
    }
    return 0;
}
