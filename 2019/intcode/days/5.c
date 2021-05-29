#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <intcode.h>

#define MAXCHAR (1000)
extern int input_register, output_register;

int main(int argc, char **argv) {
  (void)argc;

  input_register = atoi(argv[2]);
  int buffer[MAXCHAR];

  if (intcode_flash_program(buffer, argv[1])) {
    printf("Failed to open the input file!");
    return -1;
  }

  // process with intcode:
  intcode_process(buffer);
  printf("%d\n", output_register);

  return output_register;
}