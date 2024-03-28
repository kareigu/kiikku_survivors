#ifndef KIIKKU_ITEM_H
#define KIIKKU_ITEM_H
#include "common.h"

typedef enum : u8 {
  ITEM_TYPE_TEST,
} item_type_t;

typedef struct {
  item_type_t type;
  u8 level;
} item_t;


item_t item_create();

#endif
