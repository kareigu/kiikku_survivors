#ifndef KIIKKU_PLAYER_H
#define KIIKKU_PLAYER_H
#include "common.h"
#include "input.h"
#include <raylib.h>

typedef enum : u8 {
  PLAYER_STATE_AUTO_AIM = 1,
} player_state_t;

typedef struct {
  float shot_interval;
  float time_since_shot;
  float max_target_range;
} player_weapon_state_t;

typedef struct {
  Vector2 pos;
  Vector2 dir;
  stats_t stats;
  player_state_t state;
  player_weapon_state_t weapon_state;
} player_t;

player_t player_create();
player_weapon_state_t player_weapon_create();
void player_handle_input(player_t* player, inputs_t inputs);
void player_update(player_t* player);
void player_shoot(player_t* player);
void player_draw(const player_t* player);
#endif
