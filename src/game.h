#ifndef KIIKKU_GAME_H
#define KIIKKU_GAME_H

#include <raylib.h>
typedef enum {
  GAME_LOOP_STATUS_NOOP,
  GAME_LOOP_STATUS_EXIT,
} game_loop_status_t;

void game_init();
game_loop_status_t game_loop();

#endif