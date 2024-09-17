#include "../include/model.h"

namespace s21 {
GameField::GameField(int width, int height)
    : _field_width(width),
      _field_height(height),
      _snake(4, width, height),
      _apple(height, width),
      _state(GameState::RUNNING) {
  _apple.GenerateNewPosition(_snake);
}

void GameField::ChangeDirectoin(Direction new_direction) {
  _snake.SetDirectoin(new_direction);
}

GameState GameField::GetState() const { return _state; }

const Snake& GameField::GetSnake() const { return _snake; }

const Apple& GameField::GetApple() const { return _apple; }

}  // namespace s21
