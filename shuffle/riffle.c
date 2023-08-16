#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void swap(void *a, void *b, int size);
void riffle_once(void *L, int len, int size, void *work);
void print_array_str(char **arr, int len);
void print_array_int(int *arr, int len);
void riffle(void *L, int len, int size, int N);
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *));
int cmp_int(int *A, int *B);
float average_quality(int N, int shuffles, int trials);
float quality(int *numbers, int len);


// A function to swap two memory blocks of given size
void swap(void *a, void *b, int size) {
    void *temp = (void *) malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

void riffle(void *L, int len, int size, int N) {
    void *work = (void *) malloc(len * size);
    int i;

    if (work == NULL) {
        // free the allocated memory and return
        fprintf(stderr, "Memory allocation failed");
        free(work);
        exit(1);
    }

    // Perform N riffle shuffles
    for (i = 1; i <= N; i++) {
        riffle_once(L, len, size, work);

        // Swap L with work, so the current output is the input for the next iteration
        swap(L, work, len * size);
    }

    // Free the work array
    free(work);
}


// A function to perform a single riffle shuffle of the array L
void riffle_once(void *L, int len, int size, void *work) {
    // Copy the first half of L to the work array
    void *A = (void *) malloc(len / 2 * size);
    void *B = (void *) malloc((len - len / 2) * size);

    // check if allocation was successful
    if (A == NULL || B == NULL) {
        // free the allocated memory and return
        fprintf(stderr, "Memory allocation failed");
        free(A);
        free(B);
        exit(1);
    }

    // copy the first half of the array to A
    memcpy(A, L, len / 2 * size);

    // copy the second half of the array to B
    memcpy(B, L + len / 2 * size, (len - len / 2) * size);

    int a_count = 0;
    int b_count = 0;
    int use_a;
    int i;

    // Interleave the elements of A and B into work
    for (i = 0; i < len; i++) {
        int r = rand() % 2; // Generate a random number between 0 and 1
        if (r == 0) { // If r is zero, put A into work
            // Make sure that the number of times you take from A does not exceed A's length
            if (a_count >= len / 2) {
                use_a = 0;
            } else {
                use_a = 1;
            }
        } else { // If r is one, put B into work
            // Make sure that the number of times you take from B does not exceed B's length
            if (b_count >= len / 2) {
                use_a = 1;
            } else {
                use_a = 0;
            }
        }

        if (use_a == 1) {
            // Put into the memory location of work[i] the value of A[a_count]
            // In the process making A[a_count] random memory
            swap(work + (i * size), A + (a_count * size), size);
            a_count++;
        } else {
            // Put into the memory location of work[i] the value of B[b_count]
            // In the process making B[b_count] random memory
            swap(work + (i * size), B + (b_count * size), size);
            b_count++;
        }
    }
    // Free unused memory
    free(A);
    free(B);
}

// Function checks if the riffle function works as intended
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *)) {

    // Memory space for the original and the shuffled arrays
    void *original = (void *) malloc(len * size);
    void *riffled = (void *) malloc(len * size);

    if (original == NULL || riffled == NULL) {
        // free the allocated memory and return
        fprintf(stderr, "Memory allocation failed");
        free(original);
        free(riffled);
        exit(1);
    }

    // Copy contents of L into original and riffled
    memcpy(original, L, len * size);
    memcpy(riffled, L, len * size);

    // Perform a riffle shuffle on the riffled array
    riffle(riffled, len, size, 10);

    int i;
    int j;
    int orig_L_count = 0;
    int riff_orig_count = 0;

    // Count the number of times the elements in original appear in riffled
    for (i = 0; i < len; i++) {
        for (j = 0; j < len; j++) {
            if (cmp(original + (i * size), riffled + (j * size)) == 0) {
                orig_L_count++; // If original[i] is in riffled then orig_L_count += 1
            }
        }
    }

    // Count the number of times the elements in riffled appear in original
    for (i = 0; i < len; i++) {
        for (j = 0; j < len; j++) {
            if (cmp(riffled + (i * size), original + (j * size)) == 0) {
                riff_orig_count++; // If riff[i] is in original then riff_orig_count += 1
            }
        }
    }

    // Free the memory of original and riffled
    free(original);
    free(riffled);

    // Return 1 if the counts are equal to the length and the counts are equal to each other
    if (riff_orig_count == len && orig_L_count == len && orig_L_count == riff_orig_count) {
        return 1;
    }
    return 0;
}

// Function to compare two integers
int cmp_int(int *A, int *B) {
    if (*A > *B) {
        return -1;
    } else if (*A == *B) {
        return 0;
    }
    return 1;
}

// Function calculates the shuffle quality of an array *numbers
float quality(int *numbers, int len) {
    int i;
    int count = 0;
    float quality;

    // Iterate through the list
    for (i = 0; i < len - 1; i++) {
        int pair1 = numbers[i];
        int pair2 = numbers[i + 1];

        // Returns 1 if the first pair is greater than the second
        if (cmp_int(&pair1, &pair2) == 1) {
            count++;
        }
    }

    // Calculate the quality
    quality = (float) count / (float) (len - 1);

    return quality;
}

float average_quality(int N, int shuffles, int trials) {
    // Function calculates the average quality of riffle over a number of trials

    int numbers[N];
    int temp[N];
    float total_quality = 0.0f;
    int i, j;


    for (i = 0; i < N; i++) {
        numbers[i] = i;
    }

    int size = sizeof(numbers[0]);

    for (i = 0; i < trials; i++) {
        memcpy(temp, numbers, N * size);
        riffle(temp, N, size, shuffles);
        float q = quality(temp, N);
        total_quality += q;
    }

    float average_quality = total_quality / (float) trials;
    return average_quality;
}

// Function that prints an array of integers
void print_array_int(int *arr, int len) {
    printf("[");
    int i;
    for (i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i < len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// A function to print an array of integers
void print_array_str(char **arr, int len) {
    printf("[");
    int i;
    for (i = 0; i < len; i++) {
        printf("%s", arr[i]);
        if (i < len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


