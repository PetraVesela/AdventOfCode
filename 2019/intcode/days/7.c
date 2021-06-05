#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <intcode.h>

#define NUM_AMPS (5)

int process_arr(int arr[], char *filename) {
  intcode_t intcode;
  // process with intcode:
  for (int amp = 0; amp < 5; amp++) {

    intcode.input_register = arr[amp];
    if (intcode_flash_program(&intcode, filename)) {
      printf("Failed to open the input file!");
      return -1;
    }

    intcode_process(&intcode);
  }
  printf("%d\n", intcode.output_register);
  intcode.output_register = 0;
  return 0;
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
  return;
}

void heap_permutation(int arr[], int size, int n, char *filename) {
  if (size == 1) {
    process_arr(arr, filename);
  }
  for (int i = 0; i < size; i++) {
    heap_permutation(arr, size - 1, n, filename);
    if (size % 2) {
      swap(&arr[0], &arr[size - 1]);
    } else {
      swap(&arr[i], &arr[size - 1]);
    }
  }
}

int main(int argc, char **argv) {
  (void)argc;

  int permutation[NUM_AMPS];
  for (int a = 0; a < NUM_AMPS; a++) {
    permutation[a] = a;
  }
  heap_permutation(permutation, NUM_AMPS, NUM_AMPS, argv[1]);

  return 0;
}