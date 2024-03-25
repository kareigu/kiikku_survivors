#include "viewport.h"
#include "common.h"
#include <raylib.h>

static RenderTexture viewport;
static u8 current_viewport = 0;

static RenderTexture hud_viewport;

void viewport_init() {
  viewport = LoadRenderTexture(VIEWPORT_X, VIEWPORT_Y);
  hud_viewport = LoadRenderTexture(VIEWPORT_X - VIEWPORT_TILE * 2, 2 * VIEWPORT_TILE);
  TraceLog(LOG_INFO, "viewports initialised");
}

void viewport_deinit() {
  UnloadRenderTexture(viewport);
  UnloadRenderTexture(hud_viewport);
  TraceLog(LOG_INFO, "viewports unloaded");
}

RenderTexture* viewport_get() {
  return &viewport;
}

RenderTexture* viewport_get_hud() {
  return &hud_viewport;
}

void viewport_draw_scaled(Rectangle output_rect) {
  RenderTexture* viewport = viewport_get();
  Rectangle source = {.x = 0, .y = 0, .width = viewport->texture.width, .height = -viewport->texture.height};
  Vector2 origin = {.x = 0, .y = 0};
  DrawTexturePro(viewport->texture, source, output_rect, origin, 0, WHITE);
}
