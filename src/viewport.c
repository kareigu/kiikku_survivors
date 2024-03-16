#include "viewport.h"
#include "common.h"
#include <raylib.h>

static RenderTexture viewports[2];
static u8 current_viewport = 0;

void viewport_init() {
  viewports[0] = LoadRenderTexture(VIEWPORT_X, VIEWPORT_Y);
  viewports[1] = LoadRenderTexture(VIEWPORT_X, VIEWPORT_Y);
  TraceLog(LOG_INFO, "viewport initialised");
}

void viewport_new_frame() {
  current_viewport = current_viewport == 1 ? 0 : 1;
}

RenderTexture* viewport_get_current() {
  return &viewports[current_viewport];
}

u8 viewport_get_current_index() {
  return current_viewport;
}
