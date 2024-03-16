#ifndef COQUE_VIEWPORT_H
#define COQUE_VIEWPORT_H
#include "common.h"
#include <raylib.h>

#define VIEWPORT_X 200
#define VIEWPORT_Y 150

RenderTexture* viewport_get_current();
u8 viewport_get_current_index();
void viewport_init();
void viewport_new_frame();

#endif
