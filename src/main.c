#include "common.h"
#include "enemy.h"
#include "game.h"
#include "viewport.h"
#include <assert.h>
#include <raylib.h>
#include <stdbool.h>
#include <time.h>

#define RESOLUTION_X 800
#define RESOLUTION_Y 600

typedef enum {
  MAIN_STATE_MAIN_MENU,
  MAIN_STATE_LOADING,
  MAIN_STATE_GAME,
} main_state_t;

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

  main_state_t main_state = MAIN_STATE_GAME;
  game_init();

  bool should_close = false;

  while (!should_close) {
    switch (main_state) {
      case MAIN_STATE_MAIN_MENU:
      case MAIN_STATE_LOADING:
        assert(false);
      case MAIN_STATE_GAME: {
        switch (game_loop((Vector2){RESOLUTION_X, RESOLUTION_Y})) {
          case GAME_LOOP_STATUS_NOOP:
            continue;
          case GAME_LOOP_STATUS_EXIT:
            should_close = true;
            break;
        }
      }
    }

    if (WindowShouldClose())
      should_close = true;
  }

  viewport_deinit();
  CloseWindow();

  return 0;
}
