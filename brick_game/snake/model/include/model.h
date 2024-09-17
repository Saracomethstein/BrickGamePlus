#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#define HEIGHT 20
#define WIDTH 10

#include <deque>

namespace s21 {
enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

enum class GameState {
  RUNNING,
  WIN,
  GAME_OVER,
};

class Apple {
 private:
  std::pair<int, int> _position;
  int _field_height;
  int _field_width;

 public:
  Apple(int field_width, int field_height);
  void GenerateNewPosition(const Snake& snake);
  std::pair<int, int> GetPosition() const;
};

class Snake {
 private:
  void UpdatePositon();
  bool IsOutOfBounds() const;
  bool IsSelfCollision() const;

  Direction _directoin;
  std::deque<std::pair<int, int>> _body;

  int _field_height;
  int _field_width;

 public:
  Snake(int init_len, int field_width, int field_height);
  void Move();
  void Grow();
  bool CheckCollision() const;
  void SetDirectoin(Direction new_direction);
  Direction GetDirection() const;
  const std::deque<std::pair<int, int>>& GetBody() const;
  std::pair<int, int> GetHeadPositoin() const;
};

class GameField {
 private:
  int _field_height;
  int _field_width;
  Snake _snake;
  Apple _apple;
  GameState _state;

 public:
  GameField(int width, int height);
  void Update();
  void ChangeDirectoin(Direction new_directoin);
  GameState GetState() const;
  const Snake& GetSnake() const;
  const Apple& GetApple() const;
};

}  // namespace s21

#endif  // SNAKE_MODEL_H