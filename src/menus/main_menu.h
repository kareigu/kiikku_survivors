#ifndef KIIKKU_MENUS_MAIN_MENU_H
#define KIIKKU_MENUS_MAIN_MENU_H
#include <raylib.h>

typedef enum {
  MAIN_MENU_NOOP,
  MAIN_MENU_START_GAME,
  MAIN_MENU_EXIT,
} main_menu_status_t;

main_menu_status_t main_menu(Vector2 resolution);

#endif
