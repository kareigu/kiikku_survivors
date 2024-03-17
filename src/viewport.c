#include "viewport.h"
#include "common.h"
#include <raylib.h>

static RenderTexture viewports[2];
static u8 current_viewport = 0;

static RenderTexture hud_viewport;

void viewport_init() {
  viewports[0] = LoadRenderTexture(VIEWPORT_X, VIEWPORT_Y);
  viewports[1] = LoadRenderTexture(VIEWPORT_X, VIEWPORT_Y);
  hud_viewport = LoadRenderTexture(VIEWPORT_X - VIEWPORT_TILE * 2, 2 * VIEWPORT_TILE);
  TraceLog(LOG_INFO, "viewports initialised");
}

void viewport_deinit() {
  UnloadRenderTexture(viewports[0]);
  UnloadRenderTexture(viewports[1]);
  UnloadRenderTexture(hud_viewport);
  TraceLog(LOG_INFO, "viewports unloaded");
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

RenderTexture* viewport_get_hud() {
  return &hud_viewport;
}

void viewport_draw_scaled(Rectangle output_rect) {
  RenderTexture* viewport = viewport_get_current();
  Rectangle source = {.x = 0, .y = 0, .width = viewport->texture.width, .height = -viewport->texture.height};
  Vector2 origin = {.x = 0, .y = 0};
  DrawTexturePro(viewport->texture, source, output_rect, origin, 0, WHITE);
}
