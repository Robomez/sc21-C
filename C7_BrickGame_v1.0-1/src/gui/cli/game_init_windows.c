#include "cli.h"

WINDOW *CreateSubWindow(WINDOW *parent, int height, int width, int starty,
                        int startx) {
  return subwin(parent, height, width, starty, startx);
}

void InitWindows(GameWindows *windows) {
  windows->game = newwin(LINES, COLS, 0, 0);

  windows->field =
      CreateSubWindow(windows->game, FIELD_HEIGHT + 2, FIELD_WIDTH * SCALE + 2,
                      FIELD_ROW, FIELD_COL);
  windows->inner_field =
      CreateSubWindow(windows->field, FIELD_HEIGHT, FIELD_WIDTH * SCALE,
                      FIELD_ROW + 1, FIELD_COL + 1);
  windows->score = CreateSubWindow(windows->game, SCORE_HEIGHT, SCORE_WIDTH,
                                   SCORE_ROW, SCORE_COL);
  windows->high_score =
      CreateSubWindow(windows->game, HIGH_SCORE_HEIGHT, HIGH_SCORE_WIDTH,
                      HIGH_SCORE_ROW, HIGH_SCORE_COL);
  windows->next = CreateSubWindow(windows->game, NEXT_HEIGHT, NEXT_WIDTH,
                                  NEXT_ROW, NEXT_COL);
  windows->level = CreateSubWindow(windows->game, LEVEL_HEIGHT, LEVEL_WIDTH,
                                   LEVEL_ROW, LEVEL_COL);
  windows->pause = CreateSubWindow(windows->game, PAUSE_HEIGHT, PAUSE_WIDTH,
                                   PAUSE_ROW, PAUSE_COL);
  windows->hint = CreateSubWindow(windows->game, HINT_HEIGHT, HINT_WIDTH,
                                  HINT_ROW, HINT_COL);

  windows->game_over =
      CreateSubWindow(windows->game, GAME_OVER_HEIGHT, GAME_OVER_WIDTH,
                      GAME_OVER_ROW, GAME_OVER_COL);

  box(windows->game, 0, 0);
  box(windows->field, 0, 0);
  refresh();
  wnoutrefresh(windows->game);
  wnoutrefresh(windows->field);

  RenderHint(windows->hint);
}

void DeleteWindows(GameWindows *windows) {
  delwin(windows->hint);
  delwin(windows->pause);
  delwin(windows->level);
  delwin(windows->score);
  delwin(windows->high_score);
  delwin(windows->next);
  delwin(windows->inner_field);
  delwin(windows->field);
  delwin(windows->game_over);
  delwin(windows->game);
}