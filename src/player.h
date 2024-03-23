#ifndef COQUE_PLAYER_H
#define COQUE_PLAYER_H
#include "common.h"
#include "input.h"
#include <raylib.h>

typedef enum : u8 {
  PLAYER_STATE_AUTO_AIM = 1,
} player_state_t;

typedef struct {
  Vector2 pos;
  Vector2 dir;
  stats_t stats;
  player_state_t state;
} player_t;

player_t player_create();
void player_handle_input(player_t* player, inputs_t inputs);
void player_draw(player_t* player, Vector2 viewport_size);
#endif
