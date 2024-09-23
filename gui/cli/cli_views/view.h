#ifndef CLI_VIEW_H
#define CLI_VIEW_H

#include <ncurses.h>

#include "../../../controller/controller.h"

struct WinStruct {
  WINDOW *field;
  WINDOW *stats;
  WINDOW *next;
  WINDOW *help;
  WINDOW *menu;
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

  // new draw //
  // Draw menu for swith and quit game. //
  void DrawMenu(GameInfo *game, WINDOW *menu);

  // Draw all windows for tetris game. //
  void DrawTetris();

  // Draw all windows for snake game. //
  void DrawSnake();

  // Main game loop (fsm). //
  void GameLoop();

  // Classes for game (menu, state and more...) //
  enum class gMenu { TETRIS, SNAKE, QUIT };
  enum class gOverMenu { MAIN_MENU, RESTART, QUIT };
  enum class gPauseMenu { MAIN_MENU, RESTART, RESUME, QUIT };
};

#endif