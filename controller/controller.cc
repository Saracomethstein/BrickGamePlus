#include "controller.h"

GameController::GameController() : currentGame(nullptr) {}

void GameController::SetGame(GameName gn) {
  game = gn;
  switch (game) {
    case GameName::TETRIS:
      currentGame = std::make_unique<s21::TetrisGame>();
      break;

      // Edit snake class for arcade game //
      // case GameName::SNAKE:
      //   currentGame = std::make_unique<s21::Snake>();
      //   break;

    case GameName::NONE:
      currentGame.reset();
      currentGame = nullptr;
      break;
  }
}

void GameController::HandleKey(ArcadeGame::Keys key) {
  if (currentGame == nullptr) {
    return;
  }
  currentGame->HandleKey(key);
}

void GameController::MakeTick() {
  if (currentGame == nullptr) {
    return;
  }
  currentGame->MakeTick();
}

void GameController::GetData(GameInfo &gi) {
  MakeTick();
  if (currentGame != nullptr) {
    currentGame->GetData(gi);
  }
}