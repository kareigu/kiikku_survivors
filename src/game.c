#include "game.h"
#include "debug.h"
#include "enemy.h"
#include "player.h"
#include "projectile.h"
#include "renderer.h"
#include "settings.h"
#include "viewport.h"
#include <raylib.h>
#include <raymath.h>

static game_state_t game_state = {
        .player = {},
        .camera = {.offset = {0, 0}, .target = {0, 0}, .rotation = 0, .zoom = 1},
        .time_between_waves = 15,
        .time_since_prev_wave = 0,
        .stats = {
                .kills = 0,
        },
};

void game_init() {
  game_state.player = player_create();
  game_state.camera.target = Vector2Multiply(game_state.player.pos, (Vector2){(float) VIEWPORT_TILE, (float) VIEWPORT_TILE});
  projectile_buffer_init();
  enemy_spawn_wave(game_state.player.pos, GetRandomValue(50, 200));
}

void update_game_state() {
  float delta = GetFrameTime();
  game_state.time_since_prev_wave += delta;
  game_state.camera.target = Vector2Multiply(game_state.player.pos, (Vector2){(float) VIEWPORT_TILE, (float) VIEWPORT_TILE});
  float viewport_x = viewport_get()->texture.width;
  float viewport_y = viewport_get()->texture.height;
  game_state.camera.offset = (Vector2){viewport_x / 2, viewport_y / 2};
}

game_loop_status_t game_loop() {
  debug_update_data();
  input_handle();
  player_handle_input(&game_state.player, input_current());
  enemy_handle_move(game_state.player.pos);

  projectile_update(&game_state.player);
  enemy_update(&game_state.stats);

  if (input_current() & INPUT_CANCEL)
    return GAME_LOOP_STATUS_EXIT;

  update_game_state();

  if (game_state.time_since_prev_wave >= game_state.time_between_waves) {
    game_state.time_since_prev_wave = 0;
    enemy_spawn_wave(game_state.player.pos, GetRandomValue(50, 200));
    TraceLog(LOG_DEBUG, "Spawned new enemy wave");
  }

  RenderTexture* viewport = viewport_get();
  renderer_draw(viewport,
                (renderer_data_t){
                        viewport_get_hud(),
                        &game_state});

  const Vector2* resolution = settings_resolution();
  BeginDrawing();
  ClearBackground(BLACK);
  viewport_draw_scaled((Rectangle){.x = 0, .y = 0, .width = resolution->x, .height = resolution->y});
  debug_draw_display();
  EndDrawing();

  return GAME_LOOP_STATUS_NOOP;
}
