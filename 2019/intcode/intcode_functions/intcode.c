#include <intcode.h>
#include <stdio.h>

int intcode_copy_program(int *buffer, const char *filename) {
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
