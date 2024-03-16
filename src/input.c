#include "input.h"
#include <raylib.h>

static inputs_t inputs = 0;

inputs_t input_current() {
  return inputs;
}

void input_handle() {
  inputs = 0;
  for(int key = GetKeyPressed(); key != 0; key = GetKeyPressed()) {
    switch (key) {
      case KEY_UP:
      case KEY_W:
        inputs |= UP;
        continue;
      case KEY_DOWN:
      case KEY_S:
        inputs |= DOWN;
        continue;
      case KEY_LEFT:
      case KEY_A:
        inputs |= LEFT;
        continue;
      case KEY_RIGHT:
      case KEY_D:
        inputs |= RIGHT;
        continue;
      case KEY_ENTER:
        inputs |= OK;
        continue;
      case KEY_ESCAPE:
        inputs |= CANCEL;
        continue;
    }
  }
}
