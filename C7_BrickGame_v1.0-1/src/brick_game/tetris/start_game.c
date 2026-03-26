#include "backend_internal.h"

/**
 * @file start_game.c
 * @brief Функции для инициализации новой игры.
 */

/**
 * @brief Инициализирует новую игру.
 * @param game_info Указатель на структуру с игровой информацией.
 * @param figure Указатель на текущую фигуру.
 * @param next_figure Указатель на следующую фигуру.
 */
void StartGame(GameInfo_t *game_info, figure_t *figure, figure_t *next_figure) {
  srand(time(NULL) ^ getpid());

  game_info->pause = 0;
  game_info->score = 0;
  game_info->level = 1;
  game_info->speed = GetSpeedFromLevel(game_info->level);
  game_info->next = NULL;
  game_info->field = NULL;
  game_info->high_score = ReadHighScore();

  AllocateArray(&(game_info->field), FIELD_HEIGHT, FIELD_WIDTH);
  AllocateArray(&(game_info->next), NEXT_FIGURE_ROWS, NEXT_FIGURE_COLS);
  AllocateArray(&(figure->matrix), 4, 4);
  AllocateArray(&(next_figure->matrix), 4, 4);
}