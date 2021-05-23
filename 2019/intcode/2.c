#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <intcode.h>

#define MAXCHAR (1000)
#define PART_1_X (12)
#define PART_1_Y (2)
#define PART_2 (19690720)


void restore_gravity(int *buffer, const int x, const int y) {
  buffer[1] = x;
  buffer[2] = y;
  return;
};


int main(int argc, char **argv) {

  int buffer[MAXCHAR];
  if (intcode_flash_program(buffer, argv[1])) {
    printf("Failed to open the input file!");
    return -1;
  }

  // process with intcode:
  restore_gravity(buffer, PART_1_X, PART_1_Y);
  printf("Part 1: %d\n", intcode_process(buffer));

  for (int i = 0; i < 99; i++) {
    for (int j = 0; j < 99; j++) {
      intcode_flash_program(buffer, argv[1]);
      restore_gravity(buffer, i, j);
      if (intcode_process(buffer) == PART_2) {
        printf("Part 2: %d%d\n", i, j);
        return 0;
      }
    }
  }
}