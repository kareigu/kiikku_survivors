#include "player.h"
#include "input.h"
#include "viewport.h"
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
  if (inputs & UP)
    player->pos.y -= vel;
  if (inputs & DOWN)
    player->pos.y += vel;
  if (inputs & LEFT)
    player->pos.x -= vel;
  if (inputs & RIGHT)
    player->pos.x += vel;

  return;
}

void player_draw(player_t* player, Vector2 viewport_size) {
  int x = player->pos.x * VIEWPORT_TILE + viewport_size.x / 2;
  int y = player->pos.y * VIEWPORT_TILE + viewport_size.y / 2;
  DrawRectangle(x, y, VIEWPORT_TILE, VIEWPORT_TILE, GREEN);
}
