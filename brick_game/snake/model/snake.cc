#include "snake.h"

namespace s21 {
// Snake class  implementation //

Snake::Snake(int init_len, int field_widht, int field_height)
    : _field_width(field_widht),
      _field_height(field_height),
      _directoin(Direction::RIGHT) {
  for (size_t i = 0; i < init_len; i++) {
    _body.emplace_back(0, i);
  }
}

}  // namespace s21
