#ifndef KIIKKU_VIEWPORT_H
#define KIIKKU_VIEWPORT_H
#include <raylib.h>

#define VIEWPORT_X 640
#define VIEWPORT_Y 480
#define VIEWPORT_TILE VIEWPORT_X / 40

RenderTexture* viewport_get();
void viewport_init();
void viewport_deinit();

RenderTexture* viewport_get_hud();

/// Draw currently active viewport scaled to `output_rect`
void viewport_draw_scaled(Rectangle output_rect);

#endif
