#include "../include/model.h"

namespace s21 {

Apple::Apple(int field_width, int field_height)
    : _field_height(field_height), _field_width(field_width) {
  std::srand(static_cast<unsigned int>(std::time(0)));
  GenerateNewPosition(Snake(0, field_width, field_height));
}

void Apple::GenerateNewPosition(const Snake& snake) {
  bool is_on_snake = true;
  while (is_on_snake) {
    _position.first = std::rand() % _field_width;
    _position.second = std::rand() % _field_width;

    is_on_snake = false;

    for (const auto& segment : snake.GetBody()) {
      if (segment == _position) {
        is_on_snake == true;
        break;
      }
    }
  }
}

std::pair<int, int> Apple::GetPosition() const { return _position; }

}  // namespace s21
