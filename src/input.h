#ifndef COQUE_INPUT_H
#define COQUE_INPUT_H
#include "common.h"

typedef enum : u8 {
  INPUT_UP = 1,
  INPUT_DOWN = 2,
  INPUT_LEFT = 4,
  INPUT_RIGHT = 8,
  INPUT_CANCEL = 16,
  INPUT_OK = 32,
  INPUT_AUTO_AIM = 64,
} inputs_t;

void input_handle();
inputs_t input_current();

#endif
