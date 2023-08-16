#include <stdlib.h>
#include "beggar.h"
#include "riffle.h"
#include <time.h>

int main(int argc, char **argv){
    // Get the user inputted NPlayers
    int Nplayers;
    if (argc > 1) {
        Nplayers = atoi(argv[1]);
    } else {
        Nplayers = 2;
    }

    // Initialize the random number generator
    time_t t;
    srand((unsigned) time(&t));

    //                                        J   Q   K   A
    int deck[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  // Hearts
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  // Diamonds
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  // Clubs
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; // Spades

    // Shuffle the deck using riffle from Question 2
    riffle(deck, 52, sizeof(int), 10);

    beggar(Nplayers, deck, 1);
}