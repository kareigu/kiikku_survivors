#include "item.h"

item_t item_create() {
  return (item_t){
          .type = ITEM_TYPE_TEST,
          .level = 1,
          .action_interval = 1.0f,
          .time_since_action = 0.0f,
  };
}
