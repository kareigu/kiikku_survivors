#include "debug.h"
#include "viewport.h"
#include <stdio.h>
#include <raylib.h>

static char perf_display[64];

void debug_update_data() {
#ifndef NDEBUG
  sprintf(perf_display, "%d fps - %.4f ms - viewport %d", GetFPS(), GetFrameTime() * 1000, viewport_get_current_index());
#endif
}

void debug_draw_display() {
#ifndef NDEBUG
  DrawText(perf_display, 4, 4, 12, PINK);
#endif
}
