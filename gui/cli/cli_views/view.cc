#include "view.h"

void CLIView::InitCurses() {
  initscr();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  raw();
  noecho();
  cbreak();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
}

WinStruct *CLIView::InitWindows() {
  WinStruct *window = (WinStruct *)malloc(sizeof(WinStruct));
  if (window == nullptr) {
    return nullptr;
  }
  window->field = newwin(22, 22, 2, 14);
  window->stats = newwin(6, 20, 2, 36);
  window->next = newwin(7, 14, 8, 36);
  window->help = newwin(9, 20, 15, 36);
  return window;
}

void CLIView::DrawBoard(GameInfo *game, WINDOW *window) {
  box(window, 0, 0);
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      if (game->field[row][col] == 0) {
        mvwprintw(window, row + 1, 2 * col + 1, "%c", ' ');
        mvwprintw(window, row + 1, 2 * col + 2, "%c", ' ');
      } else if (game->field[row][col] == 1) {
        mvwprintw(window, row + 1, 2 * col + 1, "[");
        mvwprintw(window, row + 1, 2 * col + 2, "]");
      } else if (game->field[row][col] == 2) {
        mvwprintw(window, row + 1, 2 * col + 1, "[");
        mvwprintw(window, row + 1, 2 * col + 2, "]");
      }
    }
  }
  wrefresh(window);
}

void CLIView::DrawNext(GameInfo *game, WINDOW *next) {
  werase(next);
  box(next, 0, 0);
  wbkgd(next, COLOR_PAIR(2));
  for (int row = 0; row < BLOCK_SIZE - 1; row++) {
    for (int col = 0; col < BLOCK_SIZE; col++) {
      if (game->next[row][col] == 1) {
        mvwprintw(next, row + 1, 2 * col + 2, "[");
        mvwprintw(next, row + 1, 2 * col + 3, "]");
      } else {
        mvwprintw(next, row + 1, 2 * col + 2, " ");
        mvwprintw(next, row + 1, 2 * col + 3, " ");
      }
    }
  }
  wrefresh(next);
}

void CLIView::DrawStats(GameInfo *game, WINDOW *stats) {
  werase(stats);
  box(stats, 0, 0);
  mvwprintw(stats, 1, 1, "Stats");
  mvwprintw(stats, 2, 1, "Record: %d", game->record);
  mvwprintw(stats, 3, 1, "Score: %d", game->score);
  mvwprintw(stats, 4, 1, "Level: %d", game->level);
  wrefresh(stats);
}

void CLIView::ClearField(GameInfo *game, WINDOW *window) {
  box(window, 0, 0);
  wbkgd(window, COLOR_PAIR(1));
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      if (game->field[i][j] != 0) {
        mvwprintw(window, i + 1, 2 * j + 1, " ");
        mvwprintw(window, i + 1, 2 * j + 2, " ");
        game->field[i][j] = 0;
      }
    }
  }
  wrefresh(window);
}

void CLIView::DrawHelp(WINDOW *help) {
  werase(help);
  box(help, 0, 0);
  mvwprintw(help, 1, 1, "Left:      [<]");
  mvwprintw(help, 2, 1, "Right:     [>]");
  mvwprintw(help, 3, 1, "Down:      [v]");
  mvwprintw(help, 4, 1, "Rotate:    [space]");
  mvwprintw(help, 5, 1, "Quit:      [q]");
  mvwprintw(help, 6, 1, "Pause:     [p]");
  mvwprintw(help, 7, 1, "Restart:   [r]");
  wrefresh(help);
}

void CLIView::DrawPause(WinStruct *window) {
  wbkgdset(window->field, COLOR_PAIR(1));
  mvwprintw(window->field, 10, 8, "PAUSE");
  wrefresh(window->field);
  nodelay(stdscr, false);
  getch();
  nodelay(stdscr, true);
}

void CLIView::DrawGameOver(WinStruct *window) {
  wbkgdset(window->field, COLOR_PAIR(3));
  mvwprintw(window->field, 10, 5, "GAME OVER");
  mvwprintw(window->field, 11, 1, "Press [r] to restart");
  wrefresh(window->field);
}

void CLIView::DrawHello(GameInfo *game, WinStruct *window) {
  DrawBoard(game, window->field);
  DrawStats(game, window->stats);
  DrawNext(game, window->next);
  DrawHelp(window->help);
  mvwprintw(window->field, 10, 5, "Press any key");
  mvwprintw(window->field, 11, 6, "to continue");
  wrefresh(window->field);
  int ch = getchar();
  (void)ch;
  nodelay(window->field, true);
  game->status = Down;
}

void CLIView::DrawFrontend(GameInfo *game, WinStruct *window) {
  if (game->status == Start) {
    DrawHello(game, window);
  }

  if (game->status == Down) {
    DrawBoard(game, window->field);
    DrawStats(game, window->stats);
    DrawNext(game, window->next);
    DrawHelp(window->help);
  }

  if (game->status == Pause) {
    DrawPause(window);
  }

  if (game->status == GameOver) {
    DrawGameOver(window);
  }

  if (game->status == Restart) {
    ClearField(game, window->field);
    game->status = Down;
  }
}