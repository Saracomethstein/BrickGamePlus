#include "../include/extern_model.h"

namespace s21 {

TetrisGame::TetrisGame() { tetris_game_ = InitGame(); }
TetrisGame::~TetrisGame() { FreeGame(tetris_game_); }

GameInfo *TetrisGame::InitGame() {
  srand(time(NULL));
  GameInfo *game = (GameInfo *)malloc(sizeof(GameInfo));

  game->field = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    game->field[i] = (int *)calloc(WIDTH, sizeof(int));
  }

  game->next = (int **)calloc(BLOCK_SIZE, sizeof(int *));
  for (int i = 0; i < BLOCK_SIZE; i++) {
    game->next[i] = (int(*))calloc(BLOCK_SIZE, sizeof(int));
  }

  game->status = Start;
  LoadGame(game);

  return game;
}

void TetrisGame::LoadGame(GameInfo *game) {
  game->block_row = 0;
  game->block_col = 2;
  game->score = 0;
  game->speed = 1;
  // choose_tetromino(game);
  // place_block(game);
  // load_record(game);
}

void TetrisGame::LoadRecord(GameInfo *game) {
  FILE *file = fopen("record.txt", "r");
  if (file != NULL) {
    int number;
    if (fscanf(file, "%d", &number) == 1) {
      game->record = number;
    }
    fclose(file);
  }
}

void TetrisGame::WriteRecord(GameInfo *game) {
  FILE *file = fopen("record.txt", "w");
  if (file != NULL) {
    fprintf(file, "%d", game->record);
  }
  fclose(file);
}

void TetrisGame::FreeGame(GameInfo *game) {
  if (game) {
    if (game->field) {
      for (int i = 0; i < HEIGHT; i++) {
        if (game->field[i]) {
          free(game->field[i]);
        }
      }
      free(game->field);
    }
    if (game->next) {
      for (int i = 0; i < BLOCK_SIZE; i++) {
        if (game->next[i]) {
          free(game->next[i]);
        }
      }
      free(game->next);
    }
    free(game);
  }
}

void TetrisGame::ChooseTetromino(GameInfo *game) {
  int flag = 0;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game->next[i][j] != 0) {
        flag = 1;
        break;
      }
    }
  }

  int block_id = rand() % 7;
  int next_id = rand() % 7;

  if (flag == 0) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        game->block[i][j] = tetromino[block_id][i][j];
      }
    }
  } else {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        game->block[i][j] = game->next[i][j];
      }
    }
  }
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      game->next[i][j] = tetromino[next_id][i][j];
    }
  }
}

void TetrisGame::PlaceBlock(GameInfo *game) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game->block[i][j] == 1) {
        game->field[game->block_row + i][game->block_col + j] = 1;
      }
    }
  }
}

void TetrisGame::ClearBlock(GameInfo *game) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game->block[i][j] == 1) {
        game->field[game->block_row + i][game->block_col + j] = 0;
      }
    }
  }
}

void TetrisGame::MoveDown(GameInfo *game) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game->block[i][j] == 1) {
        int new_row = game->block_row + i + 1;
        int new_col = game->block_col + j;
        if (new_row > HEIGHT - 1 || game->field[new_row][new_col] == 2) {
          game->status = Sig;
          return;
        }
      }
    }
  }
  ClearBlock(game);
  game->block_row++;
  PlaceBlock(game);
}

void TetrisGame::MoveLeft(GameInfo *game) {
  int flag = 0;
  for (int i = 0; i < HEIGHT; i++) {
    if (game->field[i][0] == 1) {
      flag = 1;
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game->block[i][j] == 1) {
        if (game->field[game->block_row + i][game->block_col + j - 1] == 2) {
          flag = 1;
        }
      }
    }
  }

  if (flag == 1) {
    return;
  }

  ClearBlock(game);
  game->block_col--;
  PlaceBlock(game);
}

void TetrisGame::MoveRight(GameInfo *game) {
  int flag = 0;
  for (int i = 0; i < HEIGHT; i++) {
    if (game->field[i][WIDTH - 1] == 1) {
      flag = 1;
    }
  }
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game->block[i][j] == 1) {
        if (game->field[game->block_row + i][game->block_col + j + 1] == 2) {
          flag = 1;
        }
      }
    }
  }

  if (flag == 1) {
    return;
  }

  ClearBlock(game);
  game->block_col++;
  PlaceBlock(game);
}

void TetrisGame::RotateFigure(GameInfo *game) {
  int temp[BLOCK_SIZE][BLOCK_SIZE];
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      temp[i][j] = game->block[i][j];
    }
  }
  if (AllowRotation(game, temp) == 0 && CheckSquare(game)) {
    ClearBlock(game);
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        game->block[i][j] = temp[BLOCK_SIZE - j - 1][i];
      }
    }
    PlaceBlock(game);
  }
}

int TetrisGame::CheckSquare(GameInfo *game) {
  if (game->block[1][2] && game->block[2][2] && game->block[1][3] &&
      game->block[2][3])
    return 0;
  return 1;
}

void TetrisGame::CheckFinish(GameInfo *game) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (game->field[i][j] == 2) {
        game->status = GameOver;
      }
    }
  }
}

void TetrisGame::FreezeBlock(GameInfo *game) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (game->field[i][j] == 1) {
        game->field[i][j] = 2;
      }
    }
  }
}

void TetrisGame::FindFulls(GameInfo *game, int *num) {
  for (int i = HEIGHT - 1; i >= 0; i--) {
    int count = 0;
    for (int j = 0; j < WIDTH; j++) {
      if (game->field[i][j] != 0) {
        count++;
      }
    }
    if (count == WIDTH) {
      (*num) += 1;
      ClearLines(game, i);
      FindFulls(game, num);
    }
  }
}

void TetrisGame::UpdateScore(GameInfo *game, int count) {
  int step = 100;
  if (count == 1) {
    game->score += step * count;
  } else if (count == 2) {
    game->score += step * 3;
  } else if (count == 3) {
    game->score += step * 7;
  } else if (count >= 4) {
    game->score += step * 15;
  }
  if (game->score > game->record) {
    game->record = game->score;
  }
}

void TetrisGame::UpdateSpeed(GameInfo *game, int **speed) {
  int curr_speed = game->speed;
  int new_speed = game->score / 600 + 1;
  if (new_speed > 10) new_speed = 10;
  if (new_speed > curr_speed) {
    **speed = **speed - (new_speed - curr_speed) * 30;
    game->speed = new_speed;
  }
}

void TetrisGame::UpdateLevel(GameInfo *game) {
  game->level = game->score / 600 + 1;
}

void TetrisGame::ClearLines(GameInfo *game, int row_index) {
  for (int i = row_index; i > 0; i--) {
    for (int j = 0; j < WIDTH; j++) {
      game->field[i][j] = game->field[i - 1][j];
    }
  }
  for (int j = 0; j < WIDTH; j++) {
    game->field[0][j] = 0;
  }
}

int TetrisGame::AllowRotation(GameInfo *game,
                              int temp[BLOCK_SIZE][BLOCK_SIZE]) {
  int dummy[BLOCK_SIZE][BLOCK_SIZE];
  int flag = 0;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      dummy[i][j] = temp[BLOCK_SIZE - j - 1][i];
    }
  }
  int left_idx = UpBlockColLeft(dummy);
  int right_idx = UpBlockColRight(dummy);
  if (game->block_col + right_idx > 7 || game->block_col - left_idx < -2)
    flag = 1;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (dummy[i][j] == 1) {
        if (game->field[game->block_row + i][game->block_col + j] == 2 ||
            game->block_row + j + 1 > HEIGHT) {
          flag = 1;
        }
      }
    }
  }
  return flag;
}

int TetrisGame::UpBlockColLeft(int dummy[BLOCK_SIZE][BLOCK_SIZE]) {
  int pos = 2;
  int temp = 6;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (dummy[i][j] == 1 && j < pos && j < temp) {
        temp = j;
      }
    }
  }
  if (temp == 6) return 0;
  return pos - temp;
}

int TetrisGame::UpBlockColRight(int dummy[BLOCK_SIZE][BLOCK_SIZE]) {
  int pos = 2;
  int temp = -1;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (dummy[i][j] == 1 && j > pos && j > temp) {
        temp = j;
      }
    }
  }
  if (temp == -1) return 0;
  return temp - pos;
}

GameInfo TetrisGame::UpdateCurrentState(GameInfo *game, int *move_interval) {
  int count = 0;
  FreezeBlock(game);
  FindFulls(game, &count);
  if (count > 0) {
    UpdateScore(game, count);
    UpdateSpeed(game, &move_interval);
    UpdateLevel(game);
  }
  CheckFinish(game);
  if (game->status != GameOver) {
    game->block_row = 0;
    game->block_col = 2;
    ChooseTetromino(game);  // edit name //
    PlaceBlock(game);
    game->status = Down;
  }
  return *game;
}

void TetrisGame::UserInput(GameInfo *game, int hold) {
  switch (hold) {
    case Key_Space:
      game->status = Rotation;
      RotateFigure(game);
      break;
    case Key_Down:
      game->status = Down;
      MoveDown(game);
      break;
    case Key_Left:
      game->status = Left;
      MoveLeft(game);
      break;
    case Key_Right:
      game->status = Right;
      MoveRight(game);
      break;
    case Key_ESC:
      game->status = Terminate;
      break;
    case Key_Pause:
      if (game->status == Pause) {
        game->status = Sig;
      } else if (game->status != GameOver)
        game->status = Pause;
      break;
    case Key_Restart:
      game->status = Restart;
      break;
    default:
      if (game->status != GameOver && game->status != Start)
        game->status = Down;
      break;
  }
}

// This is old version //

// TetrisGame::TetrisGame() { tetris_game_ = init_game(); }

// TetrisGame::~TetrisGame() { free_game(tetris_game_); }

// void TetrisGame::HandleKey(Keys k) {
//   UserAction action;

//   switch (k) {
//     case Keys::Key_Left:
//       action = Left;
//       break;
//     case Keys::Key_Right:
//       action = Right;
//       break;

//     case Keys::Key_Up:
//       action = Up;
//       break;

//     case Keys::Key_Down:
//       action = Down;
//       break;

//     case Keys::Key_Space:
//       action = Rotation;
//       break;

//     case Keys::Key_ESC:
//       action = Terminate;
//       break;
//   }
//   user_input(tetris_game_, action);
// }

// void TetrisGame::GetData(GameInfo &gi) const {
//   gi.field = tetris_game_->field;
//   gi.next = tetris_game_->next;
//   gi.score = tetris_game_->score;
//   gi.record = tetris_game_->high_score;
//   gi.level = tetris_game_->level;
//   gi.speed = tetris_game_->speed;
//   gi.pause = tetris_game_->pause;
//   gi.block_row = tetris_game_->block_row;
//   gi.block_col = tetris_game_->block_col;
//   for (int i = 0; i < BLOCK_SIZE; ++i) {
//     for (int j = 0; j < BLOCK_SIZE; ++j) {
//       gi.block[i][j] = tetris_game_->block[i][j];
//     }
//   }
// }

// void TetrisGame::MakeTick() { move_down(tetris_game_); }

};  // namespace s21
