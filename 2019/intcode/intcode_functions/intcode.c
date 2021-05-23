#include <intcode.h>
#include <stdio.h>

static int add(const int x, const int y) { return x + y; };

static int multiply(const int x, const int y) { return x * y; };

int (*opcodes[3])(const int x, const int y) = {add, add, multiply};


int intcode_flash_program(int *buffer, const char *filename) {
  FILE *fptr;
  fptr = fopen(filename, "r");

  if (fptr == NULL) {
    perror("Error opening file\n");
    return (-1);
  };

  int i = 0;
  while (EOF != fscanf(fptr, "%d,", &buffer[i])) {
    i++;
  }
  fclose(fptr);
  return 0;
}


int intcode_process(int *buffer) {
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