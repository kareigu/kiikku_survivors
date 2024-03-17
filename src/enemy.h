#ifndef COQUE_ENEMY_H
#define COQUE_ENEMY_H
#include "common.h"
#include <raylib.h>

typedef enum : u8 {
  NONE = 0,
  TEST = 255,
} enemy_type_t;

typedef struct {
  Vector2 pos;
  stats_t stats;
  enemy_type_t type;
} enemy_t;

void enemy_init();
void enemy_create_buffer(enemy_t* buffer, u64 max_count);
void enemy_spawn_wave(enemy_t* buffer, u64 amount);
void enemy_draw(enemy_t* enemy);

#endif
