#include "enemy.h"
#include "common.h"
#include "game.h"
#include "viewport.h"
#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <string.h>

static enemy_t enemies[sizeof(enemy_type_t) * 255 + 1];
static enemy_t* s_enemy_buffer = nullptr;
static u64 s_enemy_buffer_size = 1024;

void enemy_init() {
  Vector2 pos = {0, 0};
  enemies[ENEMY_TYPE_NONE] = (enemy_t){pos, 0.0f, .stats = {0, 0, 0}, ENEMY_TYPE_NONE};
  enemies[ENEMY_TYPE_TEST] = (enemy_t){pos, 0.5f, .stats = {2, 2, 1}, ENEMY_TYPE_TEST};

  s_enemy_buffer = MemAlloc(sizeof(enemy_t) * s_enemy_buffer_size);
  assert(s_enemy_buffer);
}

void enemy_update(game_state_stats_t* stats) {
  for (u64 i = 0; i < s_enemy_buffer_size; i++) {
    enemy_t* enemy = &s_enemy_buffer[i];
    if (enemy->type == ENEMY_TYPE_NONE) continue;
    if (enemy->stats.hp == 0) {
      enemy->type = ENEMY_TYPE_NONE;
      stats->kills += 1;
      continue;
    }
  }
}

enemy_t* enemy_buffer() {
  return s_enemy_buffer;
}
u64 enemy_buffer_size() {
  return s_enemy_buffer_size;
}

void enemy_create_buffer() {
  assert(s_enemy_buffer);

  for (u64 i = 0; i < s_enemy_buffer_size; i++)
    memcpy(&s_enemy_buffer[i], &enemies[ENEMY_TYPE_NONE], sizeof(enemy_t));

  TraceLog(LOG_INFO, "enemy buffer initialised to %d", s_enemy_buffer_size);
}

void enemy_spawn_wave(Vector2 player_pos, u64 amount) {
  for (u64 i = 0; i < amount; i++) {
    if (s_enemy_buffer[i].type != ENEMY_TYPE_NONE)
      continue;

    memcpy(&s_enemy_buffer[i], &enemies[ENEMY_TYPE_TEST], sizeof(enemy_t));
    float spawn_range = GetRandomValue(25, 35);
    double r = spawn_range * sqrt(GetRandomValue(500, 1000) / 1000.0);
    double theta = (GetRandomValue(0, 1000) / 1000.0) * 2 * PI;

    int offset_x = player_pos.x + r * cos(theta);
    int offset_y = player_pos.y + r * sin(theta);
    Vector2 spawn_point = {offset_x, offset_y};
    s_enemy_buffer[i].pos = spawn_point;
  }
}

void enemy_handle_move(Vector2 player_pos) {
  float delta = GetFrameTime();
  for (u64 i = 0; i < s_enemy_buffer_size; i++) {
    enemy_t* enemy = &s_enemy_buffer[i];
    float vel = enemy->stats.vel * delta;
    switch (enemy->type) {
      case ENEMY_TYPE_NONE:
        continue;
      case ENEMY_TYPE_TEST: {
        Vector2 proposed_pos = Vector2MoveTowards(enemy->pos, player_pos, vel);
        bool colliding = false;
        for (u64 j = 0; j < s_enemy_buffer_size; j++) {
          if (j == i) continue;

          enemy_t* other = &s_enemy_buffer[j];
          if (enemy_colliding_with(other, proposed_pos, 0.5f)) {
            colliding = true;
            break;
          }
        }

        if (colliding) {
          float vel = enemy->stats.vel / 3 * delta;
          Vector2 proposed_pos = Vector2MoveTowards(enemy->pos, player_pos, vel);
          enemy->pos = proposed_pos;
        } else {
          enemy->pos = proposed_pos;
        }
        continue;
      }
    }
  }
}

bool enemy_colliding_with(enemy_t* enemy, Vector2 other_pos, float other_width) {
  return CheckCollisionCircles(enemy->pos, enemy->width, other_pos, other_width);
}

void enemy_draw(enemy_t* enemy) {
  assert(enemy);
  int x = enemy->pos.x * VIEWPORT_TILE + VIEWPORT_X / 2.0f;
  int y = enemy->pos.y * VIEWPORT_TILE + VIEWPORT_Y / 2.0f;
  switch (enemy->type) {
    case ENEMY_TYPE_NONE:
      return;
    case ENEMY_TYPE_TEST: {
      DrawRectangleRounded((Rectangle){.x = x, .y = y, .width = (float) VIEWPORT_TILE, .height = (float) VIEWPORT_TILE}, 5.0f, 4, PURPLE);
    }
  }
}
