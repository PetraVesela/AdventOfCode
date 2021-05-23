#ifndef __INTCODE__
#define __INTCODE__

int intcode_flash_program(int *buffer, const char *filename);

int intcode_process(int *buffer);

#endif // __INTCODE__
