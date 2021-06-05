#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <intcode.h>

#define MAXCHAR (1000)
#define NUM_AMPS (5)

extern int input_register, output_register;

int process_arr(int arr[], char *filename) {
  int buffer[MAXCHAR];
  // process with intcode:
  for (int amp = 0; amp < 5; amp++) {
    input_register = arr[amp];
    if (intcode_flash_program(buffer, filename)) {
      printf("Failed to open the input file!");
      return -1;
    }

    intcode_process(buffer);
  }
  printf("%d\n", output_register);
  output_register = 0;
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
  input_register = 0;
  output_register = 0;

  int permutation[NUM_AMPS];
  for (int a = 0; a < NUM_AMPS; a++) {
    permutation[a] = a;
  }
  heap_permutation(permutation, NUM_AMPS, NUM_AMPS, argv[1]);

  return output_register;
}