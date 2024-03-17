#include "enemy.h"
#include "viewport.h"
#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>

static enemy_t enemies[sizeof(enemy_type_t) * 255 + 1];

void enemy_init() {
  Vector2 pos = {0, 0};
  enemies[NONE] = (enemy_t){pos, .stats = {0, 0, 0}, NONE};
  enemies[TEST] = (enemy_t){pos, .stats = {2, 2, 1}, TEST};
}

void enemy_create_buffer(enemy_t* buffer, u64 max_count) {
  assert(buffer);

  for (u64 i = 0; i < max_count; i++)
    memcpy(&buffer[i], &enemies[NONE], sizeof(enemy_t));

  TraceLog(LOG_INFO, "enemy buffer initialised to %d", max_count);
}

void enemy_spawn_wave(enemy_t* buffer, u64 amount) {
  for (u64 i = 0; i < amount; i++) {
    memcpy(&buffer[i], &enemies[TEST], sizeof(enemy_t));
    buffer[i].pos.x = GetRandomValue(-10, 10);
    buffer[i].pos.y = GetRandomValue(-10, 10);
  }
}

void enemy_handle_move(enemy_t* buffer, u64 max_count, Vector2 player_pos) {
  for (u64 i = 0; i < max_count; i++) {
    enemy_t* enemy = &buffer[i];
    float vel = enemy->stats.vel * GetFrameTime();
    switch (enemy->type) {
      case NONE:
        continue;
      case TEST: {
        enemy->pos = Vector2MoveTowards(enemy->pos, player_pos, vel);
      }
    }
  }
}

void enemy_draw(enemy_t* enemy) {
  assert(enemy);
  int x = enemy->pos.x * VIEWPORT_TILE + VIEWPORT_X / 2.0f;
  int y = enemy->pos.y * VIEWPORT_TILE + VIEWPORT_Y / 2.0f;
  switch (enemy->type) {
    case NONE:
      return;
    case TEST: {
      DrawRectangleRounded((Rectangle){.x = x, .y = y, .width = (float) VIEWPORT_TILE, .height = (float) VIEWPORT_TILE}, 5.0f, 4, PURPLE);
    }
  }
}
