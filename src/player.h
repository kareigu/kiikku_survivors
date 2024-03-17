#ifndef COQUE_PLAYER_H
#define COQUE_PLAYER_H
#include "common.h"
#include "input.h"
#include <raylib.h>

typedef struct {
  Vector2 pos;
  Vector2 dir;
  Vector2 vel;
  u8 hp;
  u8 mp;
} player_t;

player_t player_create();
void player_handle_input(player_t* player, inputs_t inputs);
void player_draw(player_t* player, Vector2 viewport_size);
#endif
