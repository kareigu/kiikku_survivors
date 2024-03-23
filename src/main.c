#include "common.h"
#include "debug.h"
#include "enemy.h"
#include "input.h"
#include "player.h"
#include "projectile.h"
#include "renderer.h"
#include "viewport.h"
#include <raylib.h>
#include <time.h>

#define RESOLUTION_X 800
#define RESOLUTION_Y 600

int main(void) {
  InitWindow(RESOLUTION_X, RESOLUTION_Y, "kiikku survivors");
  TraceLog(LOG_INFO, "Window opened { x = %d, y = %d }", RESOLUTION_X, RESOLUTION_Y);


  viewport_init();
  enemy_init();
  SetTargetFPS(60);
  SetExitKey(0);
  SetRandomSeed(time(nullptr));

#ifndef NDEBUG
  SetTraceLogLevel(LOG_DEBUG);
#endif

  player_t player = player_create();
  projectile_buffer_init();

  enemy_spawn_wave(GetRandomValue(50, 200));

  while (!WindowShouldClose()) {
    viewport_new_frame();
    debug_update_data();
    input_handle();
    player_handle_input(&player, input_current());
    enemy_handle_move(player.pos);

    projectile_update(&player);
    enemy_update();

    if (input_current() & INPUT_CANCEL)
      break;

    RenderTexture* viewport = viewport_get_current();
    renderer_draw(viewport,
                  (renderer_data_t){
                          &player,
                          viewport_get_hud(),
                  });

    BeginDrawing();
    ClearBackground(BLACK);
    viewport_draw_scaled((Rectangle){.x = 0, .y = 0, .width = RESOLUTION_X, .height = RESOLUTION_Y});
    debug_draw_display();
    EndDrawing();
  }

  viewport_deinit();
  CloseWindow();

  return 0;
}
