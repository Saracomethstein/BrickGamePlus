#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../brick_game/common/common_class.h"
#include "../brick_game/common/common_types.h"
#include "../brick_game/snake/model/include/model.h"
#include "../brick_game/tetris/model/include/extern_model.h"

class GameController {
 public:
  GameController();
  void SetGame(GameName gn);
  void HandleKey(ArcadeGame::Keys key);
  void MakeTick();
  void GetData(GameInfo &gi);

  GameName game;
  std::unique_ptr<ArcadeGame> currentGame;
};
#endif