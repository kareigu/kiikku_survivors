#ifndef COQUE_VIEWPORT_H
#define COQUE_VIEWPORT_H
#include "common.h"
#include <raylib.h>

#define VIEWPORT_X 640
#define VIEWPORT_Y 480
#define VIEWPORT_TILE VIEWPORT_X / 40

RenderTexture* viewport_get_current();
u8 viewport_get_current_index();
void viewport_init();
void viewport_new_frame();

/// Draw currently active viewport scaled to `output_rect`
void viewport_draw_scaled(Rectangle output_rect);

#endif
