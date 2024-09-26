#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#define WIDTH 10
#define HEIGHT 20
#define TETRAMINO_COUNT 7
#define BLOCK_SIZE 5

extern const int tetromino[TETRAMINO_COUNT][BLOCK_SIZE][BLOCK_SIZE];

enum class GameName { TETRIS, SNAKE, NONE };

enum class GameState { PAUSE, GMAE_OVER, GAMING };

enum UserAction {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Rotation,
  Sig,
  GameOver,
  Restart
};

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
  int render_ready;
  int figures_stats[7];
  int stats_render_ready;
  int values_render_ready;
  int next_fig;
  int status;
  GameState state;
  int block[BLOCK_SIZE][BLOCK_SIZE];
};

#endif