#ifndef CONTROLLER_H
#define CONTROLLER_H

namespace s21 {
class GameController {
 public:
  GameController();
  void InitGame();
  void UpdateGame();
  void RenderGame();
};
}  // namespace s21
#endif