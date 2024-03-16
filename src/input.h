#ifndef COQUE_INPUT_H
#define COQUE_INPUT_H
#include "common.h"

typedef enum : u8 {
  UP = 1,
  DOWN = 2,
  LEFT = 4,
  RIGHT = 8,
  CANCEL = 16,
  OK = 32,
} inputs_t;

void input_handle();
inputs_t input_current();

#endif
