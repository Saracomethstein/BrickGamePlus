#ifndef EXTERN_MODEL_H
#define EXTERN_MODEL_H

#include <iostream>
#include <memory>

#include "../../../common/common_class.h"

namespace s21 {
class TetrisGame : public ArcadeGame {
 public:
  TetrisGame();
  ~TetrisGame() override;

  void HandleKey(Keys k) override;
  void GetData(GameInfo &gi) const override;
  void MakeTick() override;

  void UserInput(GameInfo *gameInfo, int hold);
  void ChooseTetromino(GameInfo *gameInfo);
  void LoadGame(GameInfo *gameInfo);

  void MoveLeft(GameInfo *gameInfo);
  void MoveRight(GameInfo *gameInfo);
  void MoveDown(GameInfo *gameInfo);

  void ClearBlock(GameInfo *gameInfo);
  void PlaceBlock(GameInfo *gameInfo);
  void FreezeBlock(GameInfo *gameInfo);
  void ClearLines(GameInfo *gameInfo, int row_index);

  void UpdateScore(GameInfo *gameInfo, int count);
  void UpdateSpeed(GameInfo *gameInfo, int **speed);
  void UpdateLevel(GameInfo *gameInfo);

  void LoadRecord(GameInfo *gameInfo);
  void WriteRecord(GameInfo *gameInfo);

  void FreeGame(GameInfo *gameInfo);
  void FindFulls(GameInfo *gameInfo, int *count);

  void CheckFinish(GameInfo *gameInfo);
  int CheckSquare(GameInfo *gameInfo);

  void RotateFigure(GameInfo *gameInfo);
  int UpBlockColLeft(int block[BLOCK_SIZE][BLOCK_SIZE]);
  int UpBlockColRight(int block[BLOCK_SIZE][BLOCK_SIZE]);
  int AllowRotation(GameInfo *gameInfo, int block[BLOCK_SIZE][BLOCK_SIZE]);

  GameInfo *InitGame();
  GameInfo UpdateCurrentState(GameInfo *gameInfo, int *move_interval);

 private:
  GameInfo *tetris_game_;
};
};  // namespace s21

#endif