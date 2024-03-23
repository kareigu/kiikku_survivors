#include "player.h"
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
          }};
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

  if (!Vector2Equals(pos, player->pos))
    player->dir = Vector2Normalize(Vector2Subtract(pos, player->pos));

  if (inputs & INPUT_OK && !(prev_inputs & INPUT_OK)) {
    projectile_t* projectile = projectile_create();
    projectile->dir = player->dir;
    projectile->pos = player->pos;
    projectile->vel = 8;
    projectile->type = PROJECTILE_TYPE_ONE_HIT;
    projectile->target = PROJECTILE_TARGET_ENEMY;
    projectile->source_type = PROJECTILE_TARGET_PLAYER;
    projectile->source = (void*) player;
  }

  player->pos = pos;

  prev_inputs = inputs;
  return;
}

void player_draw(player_t* player, Vector2 viewport_size) {
  assert(player);
  int x = (player->pos.x * VIEWPORT_TILE + viewport_size.x / 2);
  int y = (player->pos.y * VIEWPORT_TILE + viewport_size.y / 2);
  DrawRectangle(x - VIEWPORT_TILE / 2, y - VIEWPORT_TILE / 2, VIEWPORT_TILE, VIEWPORT_TILE, GREEN);
  DrawLineEx((Vector2){x, y}, (Vector2){x + VIEWPORT_TILE * player->dir.x, y + VIEWPORT_TILE * player->dir.y}, VIEWPORT_TILE / 8, PINK);
}
