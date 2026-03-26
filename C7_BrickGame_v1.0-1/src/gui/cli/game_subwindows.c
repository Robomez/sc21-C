#include "cli.h"

int RenderStartScreen(WINDOW *window) {
  werase(window);
  mvwprintw(window, 1, 1, "Press ENTER to start");
  wrefresh(window);
  int result = 2;

  int ch;
  while (result == 2) {
    ch = getch();
    if (ch == '\n') {
      werase(window);
      wrefresh(window);
      result = 0;
    } else if (ch == ESC) {
      werase(window);
      wrefresh(window);
      result = 1;
    }
  }
  return result;
}

void RenderField(WINDOW *window, int **field) {
  werase(window);
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      DrawBlock(window, y, x, field[y][x] ? ACS_CKBOARD : ' ');
    }
  }
  wrefresh(window);
}

void DrawBlock(WINDOW *window, int y, int x, chtype symbol) {
  mvwaddch(window, y, x * SCALE, symbol);
  if (SCALE > 1) {
    mvwaddch(window, y, x * SCALE + 1, symbol);
  }
}

void DrawFigure(WINDOW *window, int **figure, int pos_y, int pos_x) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (figure[y][x] != 0) {
        DrawBlock(window, pos_y + y, pos_x + x, ACS_CKBOARD);
      }
    }
  }
}

void RenderNextFigure(WINDOW *window, int **figure) {
  werase(window);
  wprintw(window, "NEXT:");
  DrawFigure(window, figure, 2, 0);
  wrefresh(window);
}

void RenderWindowWithText(WINDOW *window, char *text, int value) {
  werase(window);
  wprintw(window, text, value);
  wrefresh(window);
}

void RenderScore(WINDOW *window, int score) {
  RenderWindowWithText(window, "SCORE:\n%d", score);
}

void RenderLevel(WINDOW *window, int level) {
  RenderWindowWithText(window, "LEVEL:\n%d", level);
}

void RenderPause(WINDOW *window, int pause) {
  RenderWindowWithText(window, pause ? "PAUSE" : "", 0);
}

void RenderHighScore(WINDOW *window, int high_score) {
  RenderWindowWithText(window, "HI SCORE:\n%d", high_score);
}

void RenderGameOver(WINDOW *window, int score, int high_score) {
  werase(window);
  wprintw(window, "Game over. Your score: %d\nHigh score is %d\nPress ENTER",
          score, high_score);
  wrefresh(window);
}

void RenderHint(WINDOW *window) {
  werase(window);

  char *hint[] = {"Controls:\n", "space : rotate\n", "P : pause\n",
                  "ESC : exit game\n"};

  const int line_count = sizeof(hint) / sizeof(hint[0]);

  for (int i = 0; i < line_count; i++) {
    waddstr(window, hint[i]);
  }

  wrefresh(window);
}