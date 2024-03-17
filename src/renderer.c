#include "renderer.h"
#include "player.h"
#include "viewport.h"
#include <assert.h>
#include <raylib.h>
#include <stdio.h>

void renderer_hud_draw(RenderTexture* target_viewport, player_t* player) {
  assert(target_viewport);
  assert(player);
  int width = target_viewport->texture.width;
  int height = target_viewport->texture.height;

  char stats[32];
  sprintf(stats, "| HP: %d | MP: %d |", player->stats.hp, player->stats.mp);

  BeginTextureMode(*target_viewport);

  ClearBackground(ColorAlpha(WHITE, 0));
  DrawRectangleRounded((Rectangle){.x = 0, .y = 0, .width = width, .height = height}, 5.0f, 4, BLACK);
  DrawRectangleRoundedLines((Rectangle){.x = 0, .y = 1, .width = width - 2, .height = height - 2}, 5.0f, 4, 2, WHITE);

  DrawText(stats, VIEWPORT_TILE, VIEWPORT_TILE / 6, 2 * VIEWPORT_TILE, WHITE);

  EndTextureMode();
}

void renderer_draw(RenderTexture* target_viewport, renderer_data_t renderer_data) {
  player_t* player = renderer_data.player;
  RenderTexture* hud_viewport = renderer_data.hud_viewport;

  Vector2 viewport_size = {target_viewport->texture.width, target_viewport->texture.height};
  int center_x = viewport_size.x / 2;
  int center_y = viewport_size.y / 2;

  renderer_hud_draw(hud_viewport, player);

  BeginTextureMode(*target_viewport);

  ClearBackground(GRAY);
  DrawRectangleRounded((Rectangle){.x = center_x + (int) GetTime() % 5, .y = center_y + 20, .width = (float) VIEWPORT_TILE, .height = (float) VIEWPORT_TILE}, 4.0f, 4, RED);
  player_draw(player, viewport_size);

  DrawTexturePro(
          hud_viewport->texture,
          (Rectangle){.x = 0, .y = 0, .width = hud_viewport->texture.width, .height = -hud_viewport->texture.height},
          (Rectangle){.x = hud_viewport->texture.width % VIEWPORT_TILE,
                      .y = target_viewport->texture.height - 3.0f * VIEWPORT_TILE,
                      .width = hud_viewport->texture.width,
                      .height = hud_viewport->texture.height},
          (Vector2){0, 0},
          0,
          WHITE);

  EndTextureMode();
}
