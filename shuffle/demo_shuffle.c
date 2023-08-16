
#include <stdio.h>
#include <string.h>
#include "riffle.h"
#include <time.h>
#include <stdlib.h>

int main() {

    // Initialize the random nu mber generator
    time_t t;
    srand((unsigned) time(&t));

    int iterations = 15;  // number of iterations of riffle shuffles

    // Initialise the integer array
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int arr_len = sizeof(arr) / sizeof(arr[0]);
    int arr_size = sizeof(arr[0]);

    // Initialise the Greek array
    char *greek[] = {" alpha ", " beta ", " gamma ", " delta ", " epsilon ", " zeta ", " eta ", " theta ", " iota ",
                     " kappa ", " lambda ", " mu "};
    int greek_len = sizeof(greek) / sizeof(greek[0]);
    int greek_size = sizeof(greek[0]);

    // Riffle shuffle for integer array
    printf("Original integer array:\n");
    print_array_int(arr, arr_len);
    riffle(arr, arr_len, arr_size, iterations);
    printf("After %d riffle shuffles:\n", iterations);
    print_array_int(arr, arr_len);
    printf("\n");


    // Riffle shuffle for greek array
    printf("Original greek array:\n");
    print_array_str(greek, greek_len);
    riffle(greek, greek_len, greek_size, iterations);
    printf("After %d riffle shuffles:\n", iterations);
    print_array_str(greek, greek_len);
    printf("\n");

    // Check that the riffle shuffles work correctly
    int arr_check = check_shuffle(arr, arr_len, arr_size, (int (*)(void *, void *)) cmp_int);
    int greek_check = check_shuffle(greek, greek_len, greek_size, (int (*)(void *, void *)) strcmp);
    printf("Integer Check: %d - Greek Check: %d\n", arr_check, greek_check);

    return 0;
}