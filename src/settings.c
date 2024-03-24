#include "settings.h"

static settings_t s_settings = {.resolution = {800, 600}};

const settings_t* settings() {
  return &s_settings;
}

const Vector2* settings_resolution() {
  return &s_settings.resolution;
}
