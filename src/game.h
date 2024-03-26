#ifndef KIIKKU_GAME_H
#define KIIKKU_GAME_H
#include "common.h"
#include "player.h"
#include <raylib.h>

typedef enum {
  GAME_LOOP_STATUS_NOOP,
  GAME_LOOP_STATUS_EXIT,
} game_loop_status_t;

typedef struct {
  u64 kills;
} game_state_stats_t;

typedef struct {
  player_t player;
  float time_since_prev_wave;
  float time_between_waves;
  game_state_stats_t stats;
} game_state_t;

void game_init();
game_loop_status_t game_loop();

#endif
