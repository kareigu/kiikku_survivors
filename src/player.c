#include "player.h"
#include "common.h"
#include "enemy.h"
#include "input.h"
#include "item.h"
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
          .weapon_state = player_weapon_create(),
          .items = MemAlloc(sizeof(item_t) * 256),
          .items_count = 0,
  };
}

player_weapon_state_t player_weapon_create() {
  return (player_weapon_state_t){
          .shot_interval = 0.250f,
          .time_since_shot = 0.0f,
          .max_target_range = 10.0f,
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
        if (candidate_dist > player->weapon_state.max_target_range)
          continue;

        closest = candidate;
        closest_dist = candidate_dist;
      }
    }
    Vector2 old_dir = player->dir;
    player->dir = Vector2Normalize(Vector2Subtract(closest, player->pos));

    if (Vector2Equals(player->dir, (Vector2){0, 0})) {
      if (!Vector2Equals(pos, player->pos))
        player->dir = Vector2Normalize(Vector2Subtract(pos, player->pos));
      else
        player->dir = old_dir;
    }

  } else {
    if (!Vector2Equals(pos, player->pos))
      player->dir = Vector2Normalize(Vector2Subtract(pos, player->pos));
  }

  player->pos = pos;
  prev_inputs = inputs;
  return;
}

void player_update(player_t* player) {
  float delta = GetFrameTime();
  player->weapon_state.time_since_shot += delta;

  if (player->weapon_state.time_since_shot >= player->weapon_state.shot_interval) {
    player_shoot(player);
    player->weapon_state.time_since_shot = 0;
  }

  for (u8 i = 0; i < player->items_count; i++)
    player_item_update(player, &player->items[i]);
}

void player_shoot(player_t* player) {
  projectile_t* projectile = projectile_create();
  projectile->dir = player->dir;
  projectile->pos = player->pos;
  projectile->width = 0.25f;
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

void player_add_item(player_t* player, item_t item) {
  player->items[++player->items_count - 1] = item;
  TraceLog(LOG_DEBUG, "Added item #%d of type %d", player->items_count, item.type);
}

void player_item_update(player_t* player, item_t* item) {
  float delta = GetFrameTime();
  item->time_since_action += delta;

  if (item->time_since_action >= item->action_interval) {
    switch (item->type) {
      case ITEM_TYPE_TEST: {
        projectile_t* projectile = projectile_create();
        projectile->dir = Vector2Rotate(player->dir, PI);
        projectile->pos = player->pos;
        projectile->width = 0.2f;
        projectile->vel = 3;
        projectile->max_hit_count = 1;
        projectile->hit_count = 0;
        projectile->max_ttl = 10000.0f;
        projectile->ttl = 0.0f;
        projectile->type = PROJECTILE_TYPE_WOBBLER;
        projectile->target = PROJECTILE_TARGET_ENEMY;
        projectile->source_type = PROJECTILE_TARGET_PLAYER;
        projectile->source = (void*) player;
      }
    }

    item->time_since_action = 0.0f;
  }
}

void player_draw(const player_t* player) {
  assert(player);
  int x = (player->pos.x * VIEWPORT_TILE);
  int y = (player->pos.y * VIEWPORT_TILE);
  DrawRectangle(x - VIEWPORT_TILE / 2, y - VIEWPORT_TILE / 2, VIEWPORT_TILE, VIEWPORT_TILE, GREEN);
  DrawLineEx((Vector2){x, y}, (Vector2){x + (float) VIEWPORT_TILE * player->dir.x, y + (float) VIEWPORT_TILE * player->dir.y}, (float) VIEWPORT_TILE / 8, PINK);
}

void player_free(player_t* player) {
  MemFree(player->items);
  player->items_count = 0;
}
