#include "player.h"
#include "enemy.h"
#include "input.h"
#include "projectile.h"
#include "viewport.h"
#include <assert.h>
#include <raylib.h>
#include <raymath.h>

player_t player_create() {
  return (player_t){
          .pos = {.x = 0, .y = 0},
          .dir = {.x = 0, .y = -1},
          .stats = {
                  .vel = 4,
                  .hp = 6,
                  .mp = 10,
          },
          .state = 0,
  };
}

void player_handle_input(player_t* player, inputs_t inputs) {
  static inputs_t prev_inputs;
  float vel = player->stats.vel * GetFrameTime();
  Vector2 pos = player->pos;
  if (inputs & INPUT_UP)
    pos.y -= vel;
  if (inputs & INPUT_DOWN)
    pos.y += vel;
  if (inputs & INPUT_LEFT)
    pos.x -= vel;
  if (inputs & INPUT_RIGHT)
    pos.x += vel;
  player->pos = pos;

  if (inputs & INPUT_AUTO_AIM && !(prev_inputs & INPUT_AUTO_AIM)) {
    TraceLog(LOG_DEBUG, "Toggling auto aim");
    player->state ^= PLAYER_STATE_AUTO_AIM;
  }

  if (player->state & PLAYER_STATE_AUTO_AIM) {
    Vector2 closest = player->pos;
    float closest_dist = 0.0f;
    for (u64 i = 0; i < enemy_buffer_size(); i++) {
      if (enemy_buffer()[i].type == ENEMY_TYPE_NONE)
        continue;
      Vector2 candidate = enemy_buffer()[i].pos;
      float candidate_dist = Vector2Distance(player->pos, candidate);
      if (closest_dist == 0.0f || candidate_dist < closest_dist) {
        closest = candidate;
        closest_dist = candidate_dist;
      }
    }
    player->dir = Vector2Normalize(Vector2Subtract(closest, player->pos));
  } else {
    if (!Vector2Equals(pos, player->pos))
      player->dir = Vector2Normalize(Vector2Subtract(pos, player->pos));
  }

  if (inputs & INPUT_OK && !(prev_inputs & INPUT_OK))
    player_shoot(player);


  prev_inputs = inputs;
  return;
}

void player_shoot(player_t* player) {
  projectile_t* projectile = projectile_create();
  projectile->dir = player->dir;
  projectile->pos = player->pos;
  projectile->vel = 8;
  projectile->max_hit_count = 8;
  projectile->hit_count = 0;
  projectile->max_ttl = 10000.0f;
  projectile->ttl = 0.0f;
  projectile->type = PROJECTILE_TYPE_ONE_HIT;
  projectile->target = PROJECTILE_TARGET_ENEMY;
  projectile->source_type = PROJECTILE_TARGET_PLAYER;
  projectile->source = (void*) player;
}

void player_draw(player_t* player, Vector2 viewport_size) {
  assert(player);
  int x = (player->pos.x * VIEWPORT_TILE + viewport_size.x / 2);
  int y = (player->pos.y * VIEWPORT_TILE + viewport_size.y / 2);
  DrawRectangle(x - VIEWPORT_TILE / 2, y - VIEWPORT_TILE / 2, VIEWPORT_TILE, VIEWPORT_TILE, GREEN);
  DrawLineEx((Vector2){x, y}, (Vector2){x + (float) VIEWPORT_TILE * player->dir.x, y + (float) VIEWPORT_TILE * player->dir.y}, (float) VIEWPORT_TILE / 8, PINK);
}
