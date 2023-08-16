//
// Created by sammy on 29/03/2023.
//

#ifndef BEGGAR_BEGGAR_H
#define BEGGAR_BEGGAR_H

typedef struct stats {
    int shortest;
    int longest;
    float average;
} stats;
#endif //BEGGAR_BEGGAR_H

int beggar(int Nplayers, int *deck, int talkative);
stats statistics(int Nplayers, int games);
