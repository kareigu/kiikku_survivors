#include "player.h"
#include "input.h"
#include "viewport.h"
#include <assert.h>
#include <raylib.h>

player_t player_create() {
  return (player_t){
          .pos = {.x = 0, .y = 0},
          .dir = {.x = 0, .y = 0},
          .stats = {
                  .vel = 4,
                  .hp = 6,
                  .mp = 10,
          }};
}

void player_handle_input(player_t* player, inputs_t inputs) {
  float vel = player->stats.vel * GetFrameTime();
  Vector2 pos = player->pos;
  if (inputs & UP)
    pos.y -= vel;
  if (inputs & DOWN)
    pos.y += vel;
  if (inputs & LEFT)
    pos.x -= vel;
  if (inputs & RIGHT)
    pos.x += vel;

  player->pos = pos;

  return;
}

void player_draw(player_t* player, Vector2 viewport_size) {
  assert(player);
  int x = (player->pos.x * VIEWPORT_TILE + viewport_size.x / 2);
  int y = (player->pos.y * VIEWPORT_TILE + viewport_size.y / 2);
  DrawRectangle(x - VIEWPORT_TILE / 2, y - VIEWPORT_TILE / 2, VIEWPORT_TILE, VIEWPORT_TILE, GREEN);
}
