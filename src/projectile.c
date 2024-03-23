#include "projectile.h"
#include "common.h"
#include "enemy.h"
#include "viewport.h"
#include <assert.h>
#include <raylib.h>
#include <raymath.h>

static u64 s_projectile_buffer_size = 4096;
static projectile_t* s_projectile_buffer = nullptr;

projectile_t* projectile_buffer() {
  return s_projectile_buffer;
}
u64 projectile_buffer_size() {
  return s_projectile_buffer_size;
}

void projectile_buffer_init() {
  s_projectile_buffer = MemAlloc(sizeof(projectile_t) * s_projectile_buffer_size);
  for (u64 i = 0; i < s_projectile_buffer_size; i++)
    s_projectile_buffer[i] = (projectile_t){{0, 0},
                                            {0, 0},
                                            0.0f,
                                            0.0f,
                                            0,
                                            0,
                                            0.0f,
                                            0.0f,
                                            PROJECTILE_TYPE_NONE,
                                            PROJECTILE_TARGET_EMPTY,
                                            PROJECTILE_TARGET_ENEMY,
                                            nullptr};
}

void projectile_update(player_t* player) {
  float delta = GetFrameTime();
  for (u64 i = 0; i < s_projectile_buffer_size; i++) {
    projectile_t* projectile = &s_projectile_buffer[i];

    projectile->ttl += delta * 1000;
    float vel = projectile->vel * delta;

    if (projectile->hit_count >= projectile->max_hit_count) {
      projectile->type = PROJECTILE_TYPE_NONE;
      continue;
    }

    if (projectile->ttl >= projectile->max_ttl) {
      projectile->type = PROJECTILE_TYPE_NONE;
      continue;
    }

    switch (projectile->type) {
      case PROJECTILE_TYPE_NONE:
        continue;
      case PROJECTILE_TYPE_ONE_HIT: {
        projectile->pos = Vector2Add(projectile->pos, Vector2Multiply(projectile->dir, (Vector2){vel, vel}));
        switch (projectile->target) {
          case PROJECTILE_TARGET_EMPTY:
            continue;
          case PROJECTILE_TARGET_ENEMY: {
            bool collided = false;
            for (u64 i = 0; i < enemy_buffer_size(); i++) {
              enemy_t* enemy = &enemy_buffer()[i];

              if (projectile->hit_count >= projectile->max_hit_count)
                break;

              if (enemy_colliding_with(enemy, projectile->pos)) {
                collided = true;
                int damage = 99;
                if (enemy->stats.hp - damage < 0)
                  enemy->stats.hp = 0;
                else
                  enemy->stats.hp -= damage;

                projectile->hit_count++;
              }
            }
          }
          case PROJECTILE_TARGET_PLAYER: {
            continue;
          }
        }
      }
    }
  }
}

projectile_t* projectile_create() {
  assert(s_projectile_buffer);
  u64 i = 0;
  while (i < s_projectile_buffer_size) {
    if (s_projectile_buffer[i].type == PROJECTILE_TYPE_NONE) {
      TraceLog(LOG_DEBUG, "Created new projectile at index %d", i);
      return &s_projectile_buffer[i];
    }
    i++;
  }

  s_projectile_buffer_size *= 2;
  s_projectile_buffer = MemRealloc(s_projectile_buffer, s_projectile_buffer_size);
  TraceLog(LOG_DEBUG, "Reallocated projectile_buffer to %d", s_projectile_buffer_size);
  assert(s_projectile_buffer);
  while (i < s_projectile_buffer_size) {
    if (s_projectile_buffer[i].type == PROJECTILE_TYPE_NONE) {
      TraceLog(LOG_DEBUG, "Created new projectile at index %d", i);
      return &s_projectile_buffer[i];
    }
    i++;
  }
  assert(false);
}

void projectile_draw(projectile_t* projectile, Vector2 viewport_size) {
  assert(projectile);
  int x = (projectile->pos.x * VIEWPORT_TILE + viewport_size.x / 2);
  int y = (projectile->pos.y * VIEWPORT_TILE + viewport_size.y / 2);
  switch (projectile->type) {
    case PROJECTILE_TYPE_NONE:
      return;
    case PROJECTILE_TYPE_ONE_HIT: {
      DrawRectangleRounded((Rectangle){.x = x, .y = y, .width = (float) VIEWPORT_TILE / 2, .height = (float) VIEWPORT_TILE / 2}, 5.0f, 4, YELLOW);
    }
  }
}
