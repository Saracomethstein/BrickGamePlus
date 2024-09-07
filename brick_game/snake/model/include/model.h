#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#define HEIGHT 20
#define WIDTH 10

namespace s21 {

/**
 * @brief Enumeration of possible directions for the snake's movement.
 *
 * Defines the directions in which the snake can move.
 */
enum class Direction {
  UP,     ///< Move upwards.
  DOWN,   ///< Move downwards.
  LEFT,   ///< Move left.
  RIGHT,  ///< Move right.
};

/**
 * @brief Enumeration of possible game states.
 *
 * Represents the current state of the game, such as ongoing, won, or game over.
 */
enum class GameState {
  RUNNING,    ///< The game is currently running.
  WIN,        ///< The player has won the game (snake reached a certain length).
  GAME_OVER,  ///< The player has lost the game (collision with wall or self).
};

/**
 * @brief Class representing an apple in the game.
 *
 * Manages the apple's position and its regeneration when eaten by the snake.
 */
class Apple {
 private:
  std::pair<int, int> _position;  ///< Position of the apple.
  int _field_height;              ///< Height of the game field.
  int _field_width;               ///< Width of the game field.

 public:
  /**
   * @brief Constructs an Apple object.
   * @param field_width Width of the game field.
   * @param field_height Height of the game field.
   */
  Apple(int field_width, int field_height);

  /**
   * @brief Generates a new random position for the apple, ensuring it doesn't
   * collide with the snake.
   * @param snake The snake to avoid when placing the new apple.
   */
  void GenerateNewPosition(const Snake& snake);

  /**
   * @brief Retrieves the current position of the apple.
   * @return A pair representing the coordinates of the apple.
   */
  std::pair<int, int> GetPosition() const;
};

/**
 * @brief Class representing the game field.
 *
 * Manages the snake, apple, and overall game state.
 */
class GameField {
 private:
  int _field_height;  ///< Height of the game field.
  int _field_width;   ///< Width of the game field.
  Snake _snake;       ///< The snake object on the field.
  Apple _apple;       ///< The apple object on the field.
  GameState _state;   ///< The current state of the game.

 public:
  /**
   * @brief Constructs a GameField object.
   * @param width Width of the game field.
   * @param height Height of the game field.
   */
  GameField(int width, int height);

  /**
   * @brief Updates the game logic (moves snake, checks collisions, etc.).
   */
  void Update();

  /**
   * @brief Changes the snake's direction.
   * @param new_direction The new direction to set for the snake.
   */
  void ChangeDirectoin(Direction new_directoin);

  /**
   * @brief Retrieves the current state of the game.
   * @return The current game state (running, win, or game over).
   */
  GameState GetState() const;

  /**
   * @brief Retrieves the snake object.
   * @return A const reference to the snake object.
   */
  const Snake& GetSnake() const;

  /**
   * @brief Retrieves the apple object.
   * @return A const reference to the apple object.
   */
  const Apple& GetApple() const;
};

}  // namespace s21

#endif  // SNAKE_MODEL_H