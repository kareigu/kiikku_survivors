#include "input.h"
#include <raylib.h>

static inputs_t inputs = 0;

inputs_t input_current() {
  return inputs;
}

void input_handle() {
  if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    inputs |= INPUT_UP;
  else
    inputs &= ~INPUT_UP;
  if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    inputs |= INPUT_DOWN;
  else
    inputs &= ~INPUT_DOWN;
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    inputs |= INPUT_LEFT;
  else
    inputs &= ~INPUT_LEFT;
  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    inputs |= INPUT_RIGHT;
  else
    inputs &= ~INPUT_RIGHT;
  if (IsKeyDown(KEY_ESCAPE))
    inputs |= INPUT_CANCEL;
  else
    inputs &= ~INPUT_CANCEL;
  if (IsKeyDown(KEY_ENTER))
    inputs |= INPUT_OK;
  else
    inputs &= ~INPUT_OK;
}
