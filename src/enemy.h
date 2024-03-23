#ifndef COQUE_ENEMY_H
#define COQUE_ENEMY_H
#include "common.h"
#include <raylib.h>

typedef enum : u8 {
  ENEMY_TYPE_NONE = 0,
  ENEMY_TYPE_TEST = 255,
} enemy_type_t;

typedef struct {
  Vector2 pos;
  float width;
  stats_t stats;
  enemy_type_t type;
} enemy_t;

enemy_t* enemy_buffer();
u64 enemy_buffer_size();

void enemy_init();
void enemy_update();
void enemy_spawn_wave(u64 amount);
void enemy_handle_move(Vector2 player_pos);
bool enemy_colliding_with(enemy_t* enemy, Vector2 other_pos);

void enemy_draw(enemy_t* enemy);

#endif
