#include "main_menu.h"
#include "../input.h"
#include "../settings.h"
#include "../viewport.h"
#include <raylib.h>

main_menu_status_t main_menu() {
  input_handle();
  inputs_t inputs = input_current();

  if (inputs & INPUT_CANCEL)
    return MAIN_MENU_EXIT;

  if (inputs & INPUT_OK)
    return MAIN_MENU_START_GAME;

  viewport_new_frame();
  RenderTexture* viewport = viewport_get_current();

  BeginTextureMode(*viewport);
  ClearBackground(BLACK);

  const char* title = "kiikku survivors";
  int title_width = MeasureText(title, 2 * VIEWPORT_TILE);
  DrawText(title, viewport->texture.width / 2 - title_width / 2, viewport->texture.height / 2, 2 * VIEWPORT_TILE, WHITE);

  int info_text_offset_y = (viewport->texture.height / 2) + (4 * VIEWPORT_TILE);
  const char* start_text = "<ENTER> to start";
  int start_text_width = MeasureText(start_text, VIEWPORT_TILE);
  DrawText(start_text, viewport->texture.width / 2 - start_text_width / 2, info_text_offset_y, VIEWPORT_TILE, GREEN);
  const char* exit_text = "<ESC> to exit";
  int exit_text_width = MeasureText(exit_text, VIEWPORT_TILE);
  DrawText(exit_text, viewport->texture.width / 2 - exit_text_width / 2, info_text_offset_y + 2 * VIEWPORT_TILE, VIEWPORT_TILE, RED);

  EndTextureMode();


  const Vector2* resolution = settings_resolution();
  BeginDrawing();
  viewport_draw_scaled((Rectangle){0, 0, resolution->x, resolution->y});
  EndDrawing();

  return MAIN_MENU_NOOP;
}
