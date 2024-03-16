#include "debug.h"
#include "input.h"
#include "viewport.h"
#include <raylib.h>

#define RESOLUTION_X 800
#define RESOLUTION_Y 600

int main(void) {
  InitWindow(RESOLUTION_X, RESOLUTION_Y, "coque");
  TraceLog(LOG_INFO, "Window opened { x = %d, y = %d }", RESOLUTION_X, RESOLUTION_Y);


  viewport_init();
  SetTargetFPS(60);
  SetExitKey(0);
  while (!WindowShouldClose()) {
    viewport_new_frame();
    debug_update_data();
    input_handle();

    if (input_current() & CANCEL)
      break;

    RenderTexture* viewport = viewport_get_current();
    const int center_x = viewport->texture.width / 2;
    const int center_y = viewport->texture.height / 2;

    BeginTextureMode(*viewport);
    ClearBackground(GRAY);
    const char* text = "coque";
    Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 12, 0);
    DrawText(text, center_x - (int) text_size.x / 2, center_y - (int) text_size.y / 2, 12, RAYWHITE);
    DrawRectangleRounded((Rectangle){.x = center_x + (int) GetTime() % 5, .y = center_y + 20, .width = 8, .height = 8}, 4.0f, 4, RED);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    viewport_draw_scaled((Rectangle){.x = 0, .y = 0, .width = RESOLUTION_X, .height = RESOLUTION_Y});
    debug_draw_display();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
