#ifndef COQUE_RENDERER_H
#define COQUE_RENDERER_H

#include "player.h"
#include <raylib.h>
typedef struct {
  player_t* player;
} renderer_data_t;

void renderer_draw(RenderTexture* target_viewport, renderer_data_t renderer_data);

#endif
