#include "renderer.h"
#include "enemy.h"
#include "game.h"
#include "player.h"
#include "projectile.h"
#include "viewport.h"
#include <assert.h>
#include <raylib.h>
#include <stdio.h>

void renderer_hud_draw(RenderTexture* target_viewport, const game_state_t* game_state) {
  assert(target_viewport);
  assert(game_state);
  int width = target_viewport->texture.width;
  int height = target_viewport->texture.height;

  char stats[64];
  sprintf(stats, "| HP: %d | MP: %d | %llu kills |", game_state->player.stats.hp, game_state->player.stats.mp, game_state->stats.kills);

  BeginTextureMode(*target_viewport);

  ClearBackground(ColorAlpha(WHITE, 0));
  DrawRectangleRounded((Rectangle){.x = 0, .y = 0, .width = width, .height = height}, 5.0f, 4, BLACK);
  DrawRectangleRoundedLines((Rectangle){.x = 0, .y = 1, .width = width - 2, .height = height - 2}, 5.0f, 4, 2, WHITE);

  DrawText(stats, VIEWPORT_TILE, VIEWPORT_TILE / 6, 2 * VIEWPORT_TILE, WHITE);

  EndTextureMode();
}

void renderer_draw(RenderTexture* target_viewport, renderer_data_t renderer_data) {
  const game_state_t* game_state = renderer_data.game_state;
  const player_t* player = &game_state->player;
  RenderTexture* hud_viewport = renderer_data.hud_viewport;

  Vector2 viewport_size = {target_viewport->texture.width, target_viewport->texture.height};
  int center_x = viewport_size.x / 2;
  int center_y = viewport_size.y / 2;

  renderer_hud_draw(hud_viewport, game_state);

  BeginTextureMode(*target_viewport);

  ClearBackground(GRAY);
  DrawRectangleRounded((Rectangle){.x = center_x + (int) GetTime() % 5, .y = center_y + 20, .width = (float) VIEWPORT_TILE, .height = (float) VIEWPORT_TILE}, 4.0f, 4, RED);

  for (u64 i = 0; i < enemy_buffer_size(); i++) {
    enemy_draw(&enemy_buffer()[i]);
  }

  player_draw(player, viewport_size);

  for (u64 i = 0; i < projectile_buffer_size(); i++) {
    projectile_draw(&projectile_buffer()[i], viewport_size);
  }

  DrawTexturePro(
          hud_viewport->texture,
          (Rectangle){.x = 0, .y = 0, .width = hud_viewport->texture.width, .height = -hud_viewport->texture.height},
          (Rectangle){.x = hud_viewport->texture.width % VIEWPORT_TILE,// NOLINT(bugprone-integer-division): Happens due to macro expansion
                      .y = target_viewport->texture.height - 3.0f * VIEWPORT_TILE,
                      .width = hud_viewport->texture.width,
                      .height = hud_viewport->texture.height},
          (Vector2){0, 0},
          0,
          WHITE);

  EndTextureMode();
}
