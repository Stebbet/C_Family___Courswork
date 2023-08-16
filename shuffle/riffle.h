#ifndef SHUFFLING_RIFFLE_H
#define SHUFFLING_RIFFLE_H

#endif //SHUFFLING_RIFFLE_H

void riffle(void *L, int len, int size, int N);
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *));
int cmp_int(int *A, int *B);
float average_quality(int N, int shuffles, int trials);
float quality(int *numbers, int len);
void print_array_str(char **arr, int len);
void print_array_int(int *arr, int len);