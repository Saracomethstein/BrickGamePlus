#ifndef EXTERN_MODEL_H
#define EXTERN_MODEL_H

#include "../../../common/common_class.h"

// extern "C" {
// #include "model.h"
// }

namespace s21 {
class TetrisGame : public ArcadeGame {
 public:
  TetrisGame();
  ~TetrisGame() override;

  void HandleKey(Keys k) override;
  void GetData(GameInfo &gi) const override;
  void MakeTick() override;

 private:
  GameInfo_t *tetris_game_;
};
};  // namespace s21

#endif