#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <intcode.h>

#define MAXCHAR (1000)
#define PART_1_X (12)
#define PART_1_Y (2)
#define PART_2 (19690720)

int add(const int x, const int y) { return x + y; };

int multiply(const int x, const int y) { return x * y; };

int (*opcodes[3])(const int x, const int y);

void restore_gravity(int *buffer, const int x, const int y) {
  buffer[1] = x;
  buffer[2] = y;
  return;
};

int process(int *buffer) {
  int pos = 0;
  int opcode = buffer[pos];

  while (opcode != 99) {

    buffer[buffer[pos + 3]] =
        (*opcodes[opcode])(buffer[buffer[pos + 1]], buffer[buffer[pos + 2]]);
    pos += 4;
    opcode = buffer[pos];
  }
  return buffer[0];
};

int main(int argc, char **argv) {

  int buffer[MAXCHAR];
  if (intcode_copy_program(buffer, argv[1])) {
    printf("Failed to open the input file!");
    return -1;
  }

  // define array:
  opcodes[1] = add;
  opcodes[2] = multiply;

  // process with intcode:
  restore_gravity(buffer, PART_1_X, PART_1_Y);
  printf("Part 1: %d\n", process(buffer));

  for (int i = 0; i < 99; i++) {
    for (int j = 0; j < 99; j++) {
      intcode_copy_program(buffer, argv[1]);
      restore_gravity(buffer, i, j);
      if (process(buffer) == PART_2) {
        printf("Part 2: %d%d\n", i, j);
        return 0;
      }
    }
  }
}