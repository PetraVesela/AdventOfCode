#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <intcode.h>

int main(int argc, char **argv) {
  (void)argc;
  intcode_t intcode;

  intcode.input_register = atoi(argv[2]);

  if (intcode_flash_program(&intcode, argv[1])) {
    printf("Failed to open the input file!");
    return -1;
  }

  // process with intcode:
  intcode_process(&intcode);
  printf("%d\n", intcode.output_register);

  return intcode.output_register;
}