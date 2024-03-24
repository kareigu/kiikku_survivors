#ifndef KIIKKU_SETTINGS_H
#define KIIKKU_SETTINGS_H

#include <raylib.h>
typedef struct {
  Vector2 resolution;
} settings_t;

const settings_t* settings();
const Vector2* settings_resolution();

#endif
