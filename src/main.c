#include "common.h"
#include "enemy.h"
#include "game.h"
#include "menus/loading_screen.h"
#include "menus/main_menu.h"
#include "settings.h"
#include "viewport.h"
#include <raylib.h>
#include <stdbool.h>
#include <time.h>

int main(void) {
  const Vector2* resolution = settings_resolution();
  InitWindow(resolution->x, resolution->y, "kiikku survivors");
  TraceLog(LOG_INFO, "Window opened { x = %d, y = %d }", resolution->x, resolution->y);


  viewport_init();
  enemy_init();
  SetTargetFPS(60);
  SetExitKey(0);
  SetRandomSeed(time(nullptr));

#ifndef NDEBUG
  SetTraceLogLevel(LOG_DEBUG);
#endif

  main_state_t main_state = MAIN_STATE_MAIN_MENU;
  main_state_t target_main_state = MAIN_STATE_MAIN_MENU;

  bool should_close = false;

  while (!should_close) {
    switch (main_state) {
      case MAIN_STATE_MAIN_MENU: {
        switch (main_menu()) {
          case MAIN_MENU_NOOP:
            continue;
          case MAIN_MENU_START_GAME:
            target_main_state = MAIN_STATE_GAME;
            main_state = MAIN_STATE_LOADING;
            continue;
          case MAIN_MENU_EXIT:
            should_close = true;
            continue;
        }
      }
      case MAIN_STATE_LOADING: {
        loading_screen(&main_state, target_main_state);
      }
      case MAIN_STATE_GAME: {
        switch (game_loop()) {
          case GAME_LOOP_STATUS_NOOP:
            continue;
          case GAME_LOOP_STATUS_EXIT:
            target_main_state = MAIN_STATE_MAIN_MENU;
            main_state = MAIN_STATE_LOADING;
            continue;
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
