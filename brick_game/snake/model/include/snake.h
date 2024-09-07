#ifndef SNAKE_H
#define SNAKE_H

#include <deque>

#include "model.h"

namespace s21 {

/**
 * @brief Class representing the snake in the game.
 *
 * Manages the snake's position, movement, and behavior on the game field.
 */
class Snake {
 private:
  /**
   * @brief Updates the position of the snake based on its current direction.
   */
  void UpdatePositon();

  /**
   * @brief Checks if the snake is out of bounds.
   * @return true if the snake is out of the field, false otherwise.
   */
  bool IsOutOfBounds() const;

  /**
   * @brief Checks if the snake collides with itself.
   * @return true if the snake's head collides with its body, false otherwise.
   */
  bool IsSelfCollision() const;

  Direction _directoin;  ///< Current movement direction of the snake.
  std::deque<std::pair<int, int>> _body;  ///< Deque storing the snake's body
                                          ///< parts (as pairs of coordinates).
  int _field_height;                      ///< Height of the game field.
  int _field_width;                       ///< Width of the game field.

 public:
  /**
   * @brief Constructs a Snake object.
   * @param init_len Initial length of the snake.
   * @param field_width Width of the game field.
   * @param field_height Height of the game field.
   */
  Snake(int init_len, int field_width, int field_height);

  /**
   * @brief Moves the snake one step in the current direction.
   */
  void Move();

  /**
   * @brief Increases the length of the snake (called when snake eats an apple).
   */
  void Grow();

  /**
   * @brief Checks if the snake collides with walls or itself.
   * @return true if a collision is detected, false otherwise.
   */
  bool CheckCollision() const;

  /**
   * @brief Sets a new direction for the snake's movement.
   * @param new_direction The new direction to set.
   */
  void SetDirectoin(Direction new_direction);

  /**
   * @brief Gets the current direction of the snake's movement.
   * @return The current direction.
   */
  Direction GetDirection() const;

  /**
   * @brief Retrieves the current body of the snake.
   * @return A const reference to the deque storing the body of the snake.
   */
  const std::deque<std::pair<int, int>>& GetBody() const;

  /**
   * @brief Retrieves the current position of the snake's head.
   * @return A pair representing the coordinates of the snake's head.
   */
  std::pair<int, int> GetHeadPositoin() const;
};

}  // namespace s21

#endif