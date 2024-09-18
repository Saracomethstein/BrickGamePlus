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
  }
}

};  // namespace s21
