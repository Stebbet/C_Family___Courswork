
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pig.h"
#include "test_pig.h"

// A function prototype for the pig function
void pig_words (char * sentence);

// A function that takes a sentence as input and returns an array of all the words
void pig_words (char * sentence) {
    char sen[1000];  // Initialise a sentence of max length 999 characters
    strcpy(sen, sentence);
    const char tok[2] = " ";
    char *token;

    /* get the first token */
    token = strtok(sen, tok);

    /* Go though the other tokens */
    int i = 0;
    while (token  != NULL) {
        printf("%s ", pig(token)); // Convert the word to its pig latin version
        token = strtok(NULL, tok);  // Get the next token
        i++;
    }
    printf("\n");

    // Free unused memory
    free(token);
}


// A main function to test the words function
int main() {
    test_pig();
    char sentence[1000]; // a buffer to store the user input
    while (1) { // repeat until the user enters "quit"
        printf("Enter a sentence or type press enter to exit:"); // prompt the user
        // read a line from the standard input until a newline character
        if (scanf("%[^\n]%*c", sentence) <= 0){
            printf("Quitting\n");
            break;
        }
        sentence[strlen(sentence)] = '\0';
        // Compute and print the pig latin sentence
        pig_words(sentence);
    }

    return 0;
}