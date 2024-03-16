#ifndef COQUE_PLAYER_H
#define COQUE_PLAYER_H
#include "input.h"
#include <raylib.h>

typedef struct {
  Vector2 pos;
  Vector2 dir;
  Vector2 vel;
} player_t;

player_t player_create();
void player_handle_input(player_t* player, inputs_t inputs);
void player_draw(player_t* player, RenderTexture* viewport);
#endif // !DEBUG
