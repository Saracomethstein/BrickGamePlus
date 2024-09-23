#ifndef CLI_VIEW_H
#define CLI_VIEW_H

#include <ncurses.h>

#include "../../../controller/controller.h"

struct WinStruct {
  WINDOW *field;
  WINDOW *stats;
  WINDOW *next;
  WINDOW *help;
};

class CLIView {
 public:
  void InitCurses();
  void DrawBoard(GameInfo *field, WINDOW *win);
  void DrawNext(GameInfo *game, WINDOW *nextfigure);
  void DrawStats(GameInfo *game, WINDOW *stats);
  void DrawHelp(WINDOW *help);
  void DrawNext(GameInfo *game, WINDOW *next);
  void DrawGameOver(WinStruct *window);
  void DrawFrontend(GameInfo *game, WinStruct *window);
  void DrawPause(WinStruct *window);
  void DrawHello(GameInfo *game, WinStruct *window);
  void ClearField(GameInfo *game, WINDOW *window);
  WinStruct *InitWindows();
};

#endif