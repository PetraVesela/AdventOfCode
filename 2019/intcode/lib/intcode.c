#include <intcode.h>
#include <stdio.h>
#include <string.h>

// GLOBAL VARIABLES
//
int input_register, output_register, program_ctr;

// SUPPORTED INSTRUCTIONS
//
static void add(const int *params, int *buffer) {
  buffer[params[2]] = params[0] + params[1];
  return;
}

static void multiply(const int *params, int *buffer) {
  buffer[params[2]] = params[0] * params[1];
  return;
}

static void read(const int *params, int *buffer) {
  buffer[params[0]] = input_register;
  return;
}

static void write(const int *params, int *buffer) {
  output_register = buffer[params[0]];
  return;
}

static void jump_if_true(const int *params, int *buffer) {
  (void)buffer;
  if (params[0] != 0) {
    program_ctr = params[1];
  }
  return;
}

static void jump_if_false(const int *params, int *buffer) {
  (void)buffer;
  if (params[0] == 0) {
    program_ctr = params[1];
  }
  return;
}

static void less_than(const int *params, int *buffer) {
  buffer[params[2]] = params[0] < params[1];
  return;
}

static void equals(const int *params, int *buffer) {
  buffer[params[2]] = params[0] == params[1];
  return;
}

// DISPATCHER
typedef void (*function)(const int *params, int *buffer);
typedef struct {
  function func;
  int n_params;
} instruction;

static instruction instructions[9] = {
    {NULL},     {add, 3},          {multiply, 3},      {read, 1},
    {write, 1}, {jump_if_true, 2}, {jump_if_false, 2}, {less_than, 3},
    {equals, 3}};

// PARAMETER HANDLING
typedef enum { position_mode = 0, immediate_mode = 1 } intcode_parameter_mode_t;

static void eval_params(int param_modes, int *buffer, int params[],
                        const int n_params) {
  for (int i = 0; i < n_params; i++) {

    params[i] =
        (param_modes % 10 == position_mode) ? buffer[params[i]] : params[i];
    param_modes /= 10;
  }
  return;
}

// API
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
  program_ctr = 0;
  int opcode = buffer[program_ctr];
  int parsed_params[3];

  while (opcode != 99) {

    int n_params = instructions[opcode % 100].n_params;

    // copy parameters from the buffer and evaluate
    memcpy(parsed_params, &buffer[program_ctr + 1], sizeof(parsed_params));
    // Parameters that an instruction writes to will never be in immediate mode.
    if (opcode % 100 == 5 || opcode % 100 == 6) {
      eval_params(opcode / 100, buffer, parsed_params, n_params);
    } else
      eval_params(opcode / 100, buffer, parsed_params, n_params - 1);
    int tmp_pos = program_ctr;
    instructions[opcode % 100].func(parsed_params, buffer);
    if (program_ctr == tmp_pos) {
      // Only increas program_ctr, if it wasn't updated by jump instruction
      program_ctr += (n_params + 1);
    }

    opcode = buffer[program_ctr];
  }
  return buffer[0];
}