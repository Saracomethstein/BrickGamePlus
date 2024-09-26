#ifndef COMMON_CLASS_H
#define COMMON_CLASS_H

#include "common_types.h"

class ArcadeGame {
 public:
  enum Keys {
    Key_Up,
    Key_Down,
    Key_Left,
    Key_Right,
    Key_Space,
    Key_ESC,
    Key_R,
    Key_Q
  };

  virtual ~ArcadeGame() = default;
  virtual void HandleKey(Keys k) = 0;
  virtual void GetData(GameInfo &gi) const = 0;
  virtual void MakeTick() = 0;
};

#endif