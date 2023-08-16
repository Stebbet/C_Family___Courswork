#include <stdio.h>
#include <stdlib.h>
#include "riffle.h"

typedef struct stats {
    int shortest;
    int longest;
    float average;
} stats;

typedef struct node{
    int value;
    struct node *next;
} node;

typedef struct queue{
    node *head;
    node *tail;
} queue;


int dequeue(queue *q);
int enqueue(queue *p, int value);
int finished(queue *players, int Nplayers);
queue *take_turn(queue *player, queue *pile);
int beggar(int Nplayers, int *deck, int talkative);
int count_elems(queue *player);
void print_decks(queue *players, queue *pile, int Nplayers, int current_player);
void print_deck(queue *player);
stats statistics(int Nplayers, int games);


void create_queue(queue *q){
    q->head = NULL;
    q->tail = NULL;
}

int enqueue(queue *q, int value){
    // create a new node
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL){
        return 0;
    }

    new_node->value = value;
    new_node->next = NULL;

    // If there is a tail, connect the tail to the new node
    if (q->tail != NULL){
        q->tail->next = new_node;
    }
    q->tail = new_node;


    // Make sure the head is correct
    if (q->head == NULL){
        q->head = new_node;
    }
    return 1;
}

int dequeue(queue* q){
    // Check to see if the queue is empty
    if(q->head == NULL){
        return 0;
    }

    // Save the return value is the head of the list
    int result = q->head->value;

    // Remove from the list by changing the head
    q->head = q->head->next;

    return result;

}


// Function for printing the state of the decks and the pile
void print_decks(queue *players, queue *pile, int Nplayers, int current_player){
    int i;
    if (pile->head != NULL) {
        printf("Pile: ");
        print_deck(pile);
    }
    for (i = 0; i < Nplayers; i++) {
        if (i == current_player) {
            printf("* Player %d: ", i);
            print_deck(&players[i]);
        } else {
            printf("  Player %d: ", i);
            print_deck(&players[i]);
        }
    }
}

void print_deck(queue *player){
    // Pointers to the head and the tail of the player
    node *tmp = player->head;
    printf("[");
    // Print out all the elements in the players' hand
    while(tmp != NULL){
        printf("%2d", tmp->value);
        if (tmp->next != NULL) {
            printf(", ");
        }
        tmp = tmp->next;
    }
    printf("]\n");

    // Free the memory of tmp and end
    free(tmp);
}

int count_elems(queue *player){
    int count = 0;
    node *tmp = player->head;
    while (tmp != NULL){
        count++;
        tmp = tmp->next;
    }
    free(tmp);
    return count;
}

int finished(queue *players, int Nplayers) {
    int i;
    for (i = 0; i < Nplayers; i++){
        int count = count_elems(&players[i]);
        // If the count is the size of the deck
        if (count == 52) {
            return i + 1; // Can't return 0 so increment +1
        }
    }
    return 0;
}


queue *take_turn(queue *player, queue *pile){

    int i;

    // If the pile is empty
    if (pile->head == NULL){
        int card = dequeue(player);
        enqueue(pile, card);
        return NULL;
    }

    // Get the most recently pushed card
    int prev_card = pile->tail->value;

    // If the previous card is a penalty card
    if (prev_card == 11 || prev_card == 12 || prev_card == 13 || prev_card == 14){
        // Do the penalty
        for(i = 0; i < prev_card - 10; i++){
            int penalty = dequeue(player);
            if (penalty == 0){
                break;
            }
            // If one of the cards is a penalty card
            if (penalty == 11 || penalty == 12 || penalty == 13 || penalty == 14){
                // Place the card on the pile and return
                enqueue(pile, penalty);
                return NULL;
            }
            enqueue(pile, penalty);
        }
        // Make the reward the current pile
        return pile;
    } else {
        // If a penalty card is not played, place a card on the pile and return
        int card = dequeue(player);
        enqueue(pile, card);
        return NULL;
    }
}


int beggar(int Nplayers, int *deck, int talkative) {

    int i;
    int deck_len = 52;
    int turn = 0;

    // Initialise the players
    queue players[Nplayers];
    for (i = 0; i < Nplayers; i++) {
        create_queue(&players[i]);
    }

    // Initialise the pile
    queue pile;
    create_queue(&pile);

    // Deal cards to the players
    for(i = 0; i < deck_len; i++){
        enqueue(&players[i % Nplayers], deck[i]);
    }

    if (talkative != -1) {
        print_decks(players, &pile, Nplayers, -1);
        printf("\n");
    }
    int current_player;
    int is_finished = 0;
    // Game loop;
    i = 0;

    do{
        // Pointer to the current players turn

        current_player = (i % Nplayers);
        queue *player = &players[current_player];

        // The player has no cards in their hand don't take their turn
        if (player->head == NULL){
            i++;
            // Check if a player has won because this is still counted as a turn
            is_finished = finished(players, Nplayers);
            continue;
        }else{
            turn++; // Increment the turn
        }

        if (talkative != 0 && talkative != -1) {
            printf("Turn %d\n", turn);
        }

        // Player takes their turn
        queue *reward = take_turn(player, &pile);

        if (reward != NULL) {
            // Get the index of the previous player
            // The previous player can't be a player that isn't in the game
            queue *reward_player;
            int prev_player_index = current_player;
            do {
                prev_player_index -= 1;
                if (prev_player_index == -1) {
                    prev_player_index = Nplayers - 1;
                }
                reward_player = &players[prev_player_index];

            } while(reward_player->head == NULL); // Loop until there is an active player

            // Add the reward to the previous players' hand
            int r;
            node *tmp = reward->head;
            while (tmp != NULL){
                r = tmp->value;
                enqueue(reward_player, r);
                tmp = tmp->next;
            }
            free(tmp);
            // reset the pile
            create_queue(&pile);
        }
        if (talkative != 0 && talkative != -1) {
            print_decks(players, &pile, Nplayers, current_player);
            printf("\n");
        }
        is_finished = finished(players, Nplayers);
        i++;

    } while (is_finished == 0);
    if (talkative != -1) {
        printf("Player %d has won!\n", is_finished - 1);  // -1 because of the +1 in finished()
        printf("Turns taken: %d\n", turn);
    }

    return turn;
}

void create_stats(stats *p){
    p->shortest = 10000000;
    p->longest = -10000000;
    p->average = 0.0f;
}

stats statistics(int Nplayers, int games){
    int i;
    //                                        J   Q   K   A
    int deck[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  // Hearts
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  // Diamonds
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  // Clubs
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; // Spades



    stats current_stats;
    create_stats(&current_stats);

    stats *current_p = &current_stats;

    for (i = 0; i < games; i++) {
        // Shuffle the deck using riffle from Question 2
        riffle(deck, 52, sizeof(int), 10);
        int turns = beggar(Nplayers, deck, -1);

        // Check to see if it is the longest;
        if (turns > current_p->longest){
            current_p->longest = turns;
        }

        // Check to see if it is the smallest;
        if (turns < current_p->shortest){
            current_p->shortest = turns;
        }

        // Add the number of turns to the average
        current_p->average += (float)turns;
    }

    // Calculate the average
    current_p->average /= (float)games;
    return current_stats;
}