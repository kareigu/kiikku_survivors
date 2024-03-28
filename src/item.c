#include "item.h"

item_t item_create() {
  return (item_t){
          .type = ITEM_TYPE_TEST,
          .level = 1,
  };
}
