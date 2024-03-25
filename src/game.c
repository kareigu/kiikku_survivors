#include "game.h"
#include "debug.h"
#include "enemy.h"
#include "player.h"
#include "projectile.h"
#include "renderer.h"
#include "settings.h"
#include "viewport.h"
#include <raylib.h>

static player_t player;

void game_init() {
  player = player_create();
  projectile_buffer_init();
  enemy_spawn_wave(player.pos, GetRandomValue(50, 200));
}

game_loop_status_t game_loop() {
  viewport_new_frame();
  debug_update_data();
  input_handle();
  player_handle_input(&player, input_current());
  enemy_handle_move(player.pos);

  projectile_update(&player);
  enemy_update();

  if (input_current() & INPUT_CANCEL)
    return GAME_LOOP_STATUS_EXIT;

  RenderTexture* viewport = viewport_get_current();
  renderer_draw(viewport,
                (renderer_data_t){
                        &player,
                        viewport_get_hud(),
                });

  const Vector2* resolution = settings_resolution();
  BeginDrawing();
  ClearBackground(BLACK);
  viewport_draw_scaled((Rectangle){.x = 0, .y = 0, .width = resolution->x, .height = resolution->y});
  debug_draw_display();
  EndDrawing();

  return GAME_LOOP_STATUS_NOOP;
}
