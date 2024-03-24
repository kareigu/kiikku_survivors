#include "loading_screen.h"
#include "../game.h"
#include "../settings.h"
#include "../viewport.h"
#include <assert.h>
#include <raylib.h>

void loading_screen(main_state_t* main_state, main_state_t target_main_state) {
  viewport_new_frame();
  RenderTexture* viewport = viewport_get_current();

  BeginTextureMode(*viewport);

  ClearBackground(BLACK);

  const char* text = "loading";
  int title_width = MeasureText(text, 2 * VIEWPORT_TILE);
  DrawText(text, viewport->texture.width / 2 - title_width / 2, viewport->texture.height / 2, 2 * VIEWPORT_TILE, WHITE);

  EndTextureMode();

  const Vector2* resolution = settings_resolution();
  BeginDrawing();
  ClearBackground(BLACK);
  viewport_draw_scaled((Rectangle){0, 0, resolution->x, resolution->y});
  EndDrawing();

  switch (target_main_state) {
    case MAIN_STATE_MAIN_MENU:
      *main_state = MAIN_STATE_MAIN_MENU;
      return;
    case MAIN_STATE_GAME:
      game_init();
      *main_state = MAIN_STATE_GAME;
      return;
    case MAIN_STATE_LOADING:
      TraceLog(LOG_ERROR, "Cannot load to loading screen");
      assert(false);
      return;
  }
}
