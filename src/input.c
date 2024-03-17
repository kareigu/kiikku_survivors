#include "input.h"
#include <raylib.h>

static inputs_t inputs = 0;

inputs_t input_current() {
  return inputs;
}

void input_handle() {
  if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    inputs |= UP;
  else
    inputs &= ~UP;
  if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    inputs |= DOWN;
  else
    inputs &= ~DOWN;
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    inputs |= LEFT;
  else
    inputs &= ~LEFT;
  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    inputs |= RIGHT;
  else
    inputs &= ~RIGHT;
  if (IsKeyDown(KEY_ESCAPE))
    inputs |= CANCEL;
  else
    inputs &= ~CANCEL;
  if (IsKeyDown(KEY_ENTER))
    inputs |= OK;
  else
    inputs &= ~OK;
}
