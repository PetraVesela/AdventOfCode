#include <intcode.h>
#include <stdio.h>
#include <string.h>

static int input_num = 0;

// SUPPORTED INSTRUCTIONS
//
static void add(intcode_t *me, const int *params) {
  me->buffer[params[2]] = params[0] + params[1];
  return;
}

static void multiply(intcode_t *me, const int *params) {
  me->buffer[params[2]] = params[0] * params[1];
  return;
}

static void read(intcode_t *me, const int *params) {
  if (input_num == 0) {
    me->buffer[params[0]] = me->input_register;
    input_num++;
  } else {
    me->buffer[params[0]] = me->output_register;
    input_num = 0;
  }

  return;
}

static void write(intcode_t *me, const int *params) {
  me->output_register = me->buffer[params[0]];
  return;
}

static void jump_if_true(intcode_t *me, const int *params) {
  if (params[0] != 0) {
    me->program_ctr = params[1];
  }
  return;
}

static void jump_if_false(intcode_t *me, const int *params) {

  if (params[0] == 0) {
    me->program_ctr = params[1];
  }
  return;
}

static void less_than(intcode_t *me, const int *params) {
  me->buffer[params[2]] = params[0] < params[1];
  return;
}

static void equals(intcode_t *me, const int *params) {
  me->buffer[params[2]] = params[0] == params[1];
  return;
}

// DISPATCHER
typedef void (*function)(intcode_t *me, const int *params);
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
int intcode_flash_program(intcode_t *me, const char *filename) {
  FILE *fptr;
  fptr = fopen(filename, "r");

  if (fptr == NULL) {
    perror("Error opening file\n");
    return (-1);
  };

  int i = 0;
  while (EOF != fscanf(fptr, "%d,", &me->buffer[i])) {
    i++;
  }
  fclose(fptr);
  return 0;
}

int intcode_process(intcode_t *me) {
  me->program_ctr = 0;
  int opcode = me->buffer[me->program_ctr];
  int parsed_params[3];

  while (opcode != 99) {

    int n_params = instructions[opcode % 100].n_params;

    // copy parameters from the buffer and evaluate
    memcpy(parsed_params, &me->buffer[me->program_ctr + 1],
           sizeof(parsed_params));
    // Parameters that an instruction writes to will never be in immediate mode.
    if (opcode % 100 == 5 || opcode % 100 == 6) {
      eval_params(opcode / 100, me->buffer, parsed_params, n_params);
    } else
      eval_params(opcode / 100, me->buffer, parsed_params, n_params - 1);
    int tmp_pos = me->program_ctr;
    instructions[opcode % 100].func(me, parsed_params);
    if (me->program_ctr == tmp_pos) {
      // Only increase me->program_ctr, if it wasn't updated by jump instruction
      me->program_ctr += (n_params + 1);
    }

    opcode = me->buffer[me->program_ctr];
  }
  return me->buffer[0];
}
