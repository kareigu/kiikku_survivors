#include "common.h"
#include "debug.h"
#include "enemy.h"
#include "input.h"
#include "player.h"
#include "renderer.h"
#include "viewport.h"
#include <raylib.h>

#define RESOLUTION_X 800
#define RESOLUTION_Y 600

int main(void) {
  InitWindow(RESOLUTION_X, RESOLUTION_Y, "coque");
  TraceLog(LOG_INFO, "Window opened { x = %d, y = %d }", RESOLUTION_X, RESOLUTION_Y);


  viewport_init();
  enemy_init();
  SetTargetFPS(60);
  SetExitKey(0);

  player_t player = player_create();
  u64 max_enemies = 1024;
  enemy_t enemies[max_enemies];
  enemy_create_buffer(enemies, max_enemies);

  enemy_spawn_wave(enemies, GetRandomValue(5, 8));

  while (!WindowShouldClose()) {
    viewport_new_frame();
    debug_update_data();
    input_handle();
    player_handle_input(&player, input_current());

    if (input_current() & CANCEL)
      break;

    RenderTexture* viewport = viewport_get_current();
    renderer_draw(viewport,
                  (renderer_data_t){&player,
                                    viewport_get_hud(),
                                    enemies,
                                    max_enemies});

    BeginDrawing();
    ClearBackground(BLACK);
    viewport_draw_scaled((Rectangle){.x = 0, .y = 0, .width = RESOLUTION_X, .height = RESOLUTION_Y});
    debug_draw_display();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
