#ifndef KIIKKU_RENDERER_H
#define KIIKKU_RENDERER_H
#include "game.h"
#include <raylib.h>

typedef struct {
  RenderTexture* hud_viewport;
  const game_state_t* game_state;
} renderer_data_t;

void renderer_init();
void renderer_draw(RenderTexture* target_viewport, renderer_data_t renderer_data);

#endif
