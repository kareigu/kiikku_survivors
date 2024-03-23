#ifndef COQUE_PROJECTILE_H
#define COQUE_PROJECTILE_H
#include "common.h"
#include "player.h"
#include <raylib.h>

typedef enum {
  PROJECTILE_TYPE_NONE,
  PROJECTILE_TYPE_ONE_HIT,
} projectile_type_t;

typedef enum {
  PROJECTILE_TARGET_EMPTY,
  PROJECTILE_TARGET_ENEMY,
  PROJECTILE_TARGET_PLAYER,
} projectile_target_t;

typedef struct {
  Vector2 pos;
  Vector2 dir;
  float vel;
  u32 max_hit_count;
  u32 hit_count;
  float max_ttl;
  float ttl;
  projectile_type_t type;
  projectile_target_t target;
  projectile_target_t source_type;
  void* source;
} projectile_t;

void projectile_buffer_init();
void projectile_update(player_t* player);

projectile_t* projectile_create();
void projectile_draw(projectile_t* projectile, Vector2 viewport_size);

projectile_t* projectile_buffer();
u64 projectile_buffer_size();

#endif
