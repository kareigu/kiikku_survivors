#include "player.h"
#include "input.h"
#include <raylib.h>

player_t player_create() {
  return (player_t){
    .pos = {.x = 0, .y = 0},
    .dir = {.x = 0, .y = 0},
    .vel = {.x = 0, .y = 0},
  };
}

void player_handle_input(player_t* player, inputs_t inputs) {
  if (inputs & UP)
    player->pos.y--;
  if (inputs & DOWN)
    player->pos.y++;
  if (inputs & LEFT)
    player->pos.x--;
  if (inputs & RIGHT)
    player->pos.x++;

  return;
}

void player_draw(player_t* player, Vector2 viewport_size) {
  int x = (int)player->pos.x + viewport_size.x / 2;
  int y = (int)player->pos.y + viewport_size.y / 2;
  DrawRectangle(x, y, 4, 4, GREEN);
}
