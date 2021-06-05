#ifndef __INTCODE__
#define __INTCODE__

#define MAX_LEN (1000)
typedef struct intcode_t {
  int buffer[MAX_LEN];
  int input_register;
  int output_register;
  int program_ctr;

} intcode_t;

int intcode_flash_program(intcode_t *me, const char *filename);
int intcode_process(intcode_t *me);

#endif // __INTCODE__
