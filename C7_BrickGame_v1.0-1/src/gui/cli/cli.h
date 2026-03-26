#ifndef CLI_H_
#define CLI_H_

#include <ncurses.h>

#include "../../brick_game/tetris/backend.h"
#include "defines.h"

typedef struct {
  WINDOW *game;
  WINDOW *field;
  WINDOW *inner_field;
  WINDOW *score;
  WINDOW *high_score;
  WINDOW *next;
  WINDOW *level;
  WINDOW *pause;
  WINDOW *hint;
  WINDOW *game_over;
} GameWindows;

void RenderGame();
int UserActionHandler();

void InitWindows(GameWindows *windows);
void DeleteWindows(GameWindows *windows);

int RenderStartScreen(WINDOW *window);
void RenderField(WINDOW *window, int **field);
void RenderScore(WINDOW *window, int score);
void RenderLevel(WINDOW *window, int level);
void RenderHighScore(WINDOW *window, int high_score);
void RenderNextFigure(WINDOW *window, int **figure);
void DrawBlock(WINDOW *window, int y, int x, chtype symbol);
void DrawFigure(WINDOW *window, int **figure, int pos_y, int pos_x);
void RenderHint(WINDOW *window);
void RenderPause(WINDOW *window, int paused);
void RenderGameOver(WINDOW *window, int score, int high_score);

#endif