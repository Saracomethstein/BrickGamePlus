#include "../include/extern_model.h"

namespace s21 {

TetrisGame::TetrisGame() { tetris_game_ = init_game(); }

TetrisGame::~TetrisGame() { free_game(tetris_game_); }

void TetrisGame::HandleKey(Keys k) {
  UserAction_t action;

  switch (k) {
    case Keys::Key_Left:
      action = Left;
      break;
    case Keys::Key_Right:
      action = Right;
      break;

    case Keys::Key_Up:
      action = Up;
      break;

    case Keys::Key_Down:
      action = Down;
      break;

    case Keys::Key_Space:
      action = Rotation;
      break;

    case Keys::Key_ESC:
      action = Terminate;
      break;
  }
  user_input(tetris_game_, action);
}

void TetrisGame::GetData(GameInfo &gi) const {
  gi.field = tetris_game_->field;
  gi.next = tetris_game_->next;
  gi.score = tetris_game_->score;
  gi.record = tetris_game_->high_score;
  gi.level = tetris_game_->level;
  gi.speed = tetris_game_->speed;
  gi.pause = tetris_game_->pause;
  gi.block_row = tetris_game_->block_row;
  gi.block_col = tetris_game_->block_col;
  for (int i = 0; i < BLOCK_SIZE; ++i) {
    for (int j = 0; j < BLOCK_SIZE; ++j) {
      gi.block[i][j] = tetris_game_->block[i][j];
    }
  }
}

void TetrisGame::MakeTick() { move_down(tetris_game_); }

};  // namespace s21
