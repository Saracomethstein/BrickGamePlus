#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#define WIDTH 10
#define HEIGHT 20
#define TETRAMINO_COUNT 7
#define BLOCK_SIZE 5

struct GameInfo {
  int **field;
  int **next;
  int score;
  int record;
  int level;
  int speed;
  int pause;
  int block_row;
  int block_col;
  int block[BLOCK_SIZE][BLOCK_SIZE];
  GameState state;
};

enum class GameName {
  TETRIS,
  SNAKE,
  NONE,
};

enum class GameState {
  PAUSE,
  GMAE_OVER,
  GAMING,
};

#endif