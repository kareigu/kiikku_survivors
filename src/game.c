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

static game_state_t game_state = {
        .time_between_waves = 15,
        .time_since_prev_wave = 0,
};

void game_init() {
  player = player_create();
  projectile_buffer_init();
  enemy_spawn_wave(player.pos, GetRandomValue(50, 200));
}

void update_game_state() {
  float delta = GetFrameTime();
  game_state.time_since_prev_wave += delta;
}

game_loop_status_t game_loop() {
  debug_update_data();
  input_handle();
  player_handle_input(&player, input_current());
  enemy_handle_move(player.pos);

  projectile_update(&player);
  enemy_update();

  if (input_current() & INPUT_CANCEL)
    return GAME_LOOP_STATUS_EXIT;

  update_game_state();

  if (game_state.time_since_prev_wave >= game_state.time_between_waves) {
    game_state.time_since_prev_wave = 0;
    enemy_spawn_wave(player.pos, GetRandomValue(50, 200));
    TraceLog(LOG_DEBUG, "Spawned new enemy wave");
  }

  RenderTexture* viewport = viewport_get();
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
