#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char * pig(char * word);
int is_vowel(char c);


/* A function that takes a word and returns its Pig Latin version */
char * pig (char * word) {
    /* Allocate memory for the result */
    char * result = malloc(strlen(word) + 3);

    char first = tolower(word[0]);

    /* Check if the character is a vowel */
    if (is_vowel(first) == 1) {
        /* If yes, append "way" to the word */
        sprintf(result, "%sway", word);
    } else {
        // If no, find the index of the first vowel in the word
        int index = 1;
        while (word[index] != '\0') {
            char c = tolower(word[index]);
            if (is_vowel(c) == 1) {
                // If a vowel is found, break the loop
                break;
            } else if (c == 'y') {
                // If a "y" is found, check if it follows consonants
                if (index >= 1) {
                    // If yes, treat it as a vowel and break the loop
                    break;
                } else {
                    // If no, treat it as a consonant and continue the loop
                    index++;
                }
            } else {
                // If a consonant is found, continue the loop
                index++;
            }
        }
        // Move the letters before the first vowel to the end and append "ay"
        sprintf(result, "%s%.*say", word + index, index, word);
    }
    // Return the result
    return result;
}


int is_vowel(char c){
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
        return 1;
    }
    return 0;
}