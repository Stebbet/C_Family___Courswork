//
// Created by sammy on 25/03/2023.
//
#include <stdio.h>
#include "pig.h"

void test_pig(){
    char words[7][10] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal"};
    int i;
    for (i = 0; i < 7; i++){
        printf("%s => %s\n", words[i], pig(words[i]));
    }
}