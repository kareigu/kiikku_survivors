#include "renderer.h"
#include "player.h"
#include "viewport.h"
#include <raylib.h>

void renderer_draw(RenderTexture* target_viewport, renderer_data_t renderer_data) {
  player_t* player = renderer_data.player;

  Vector2 viewport_size = {target_viewport->texture.width, target_viewport->texture.height};
  int center_x = viewport_size.x / 2;
  int center_y = viewport_size.y / 2;

  BeginTextureMode(*target_viewport);

  ClearBackground(GRAY);
  const char* text = "coque";
  Vector2 text_size = MeasureTextEx(GetFontDefault(), text, (float)VIEWPORT_TILE, 0); 
  DrawText(text, center_x - (int) text_size.x / 2, center_y - (int) text_size.y / 2, VIEWPORT_TILE, RAYWHITE);
  DrawRectangleRounded((Rectangle){.x = center_x + (int) GetTime() % 5, .y = center_y + 20, .width = (float)VIEWPORT_TILE, .height = (float)VIEWPORT_TILE}, 4.0f, 4, RED);
  player_draw(player, viewport_size);

  EndTextureMode();
}
