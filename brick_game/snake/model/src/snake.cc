#include "model.h"

namespace s21 {

Snake::Snake(int init_len, int field_widht, int field_height)
    : _field_width(field_widht),
      _field_height(field_height),
      _directoin(Direction::RIGHT) {
  for (size_t i = 0; i < init_len; i++) {
    _body.emplace_back(0, i);
  }
}

void Snake::Move() {
  UpdatePositon();
  _body.pop_back();
}

// New snake len //
void Snake::Grow() { _body.push_back(_body.back()); }

bool Snake::CheckCollision() const {
  return IsOutOfBounds() || IsSelfCollision();
}

// Snake can't turn 180 degrees //
void Snake::SetDirectoin(Direction new_direction) {
  if ((_directoin == Direction::UP && new_direction != Direction::DOWN) ||
      (_directoin == Direction::DOWN && new_direction != Direction::UP) ||
      (_directoin == Direction::LEFT && new_direction != Direction::RIGHT) ||
      (_directoin == Direction::RIGHT && new_direction != Direction::LEFT)) {
    _directoin = new_direction;
  }
}

Direction Snake::GetDirection() const { return _directoin; }

const std::deque<std::pair<int, int>>& Snake::GetBody() const { return _body; }

std::pair<int, int> Snake::GetHeadPositoin() const { return _body.front(); }

void Snake::UpdatePositon() {
  int x = _body.front().first;
  int y = _body.front().second;

  switch (_directoin) {
    case Direction::UP:
      y--;
      break;

    case Direction::DOWN:
      y++;
      break;

    case Direction::LEFT:
      x--;
      break;

    case Direction::RIGHT:
      x++;
      break;
  }

  _body.emplace_front(x, y);
}

bool Snake::IsOutOfBounds() const {
  auto head = _body.front();
  return head.first < 0 || head.first >= _field_width || head.second < 0 ||
         head.second >= _field_height;
}

bool Snake::IsSelfCollision() const {
  auto head = _body.front();
  for (size_t i = 1; i < _body.size(); i++) {
    if (_body[i] == head) {
      return true;
    }
  }
  return false;
}

}  // namespace s21
