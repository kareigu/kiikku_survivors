#include "debug.h"
#include <raylib.h>
#include <stdio.h>

static char perf_display[64];

void debug_update_data() {
#ifndef NDEBUG
  sprintf(perf_display, "%d fps - %.4f ms", GetFPS(), GetFrameTime() * 1000);
#endif
}

void debug_draw_display() {
#ifndef NDEBUG
  DrawText(perf_display, 4, 4, 12, PINK);
#endif
}
