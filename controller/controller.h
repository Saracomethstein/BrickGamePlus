#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

#include "../brick_game/common/common_class.h"
#include "../brick_game/common/common_types.h"
#include "../brick_game/tetris/model/include/model.h"
// include snake model //

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