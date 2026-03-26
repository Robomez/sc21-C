#include <stdio.h>

#include "backend_internal.h"

/**
 * @file stop_game.c
 * @brief Функции для завершения игры.
 */

/**
 * @brief Освобождает ресурсы и завершает игру.
 * @param game_info Указатель на структуру с игровой информацией.
 * @param figure Указатель на текущую фигуру.
 * @param next_figure Указатель на следующую фигуру.
 */
void StopGame(GameInfo_t *game_info, figure_t *figure, figure_t *next_figure) {
  FreeMemory(game_info, figure, next_figure);
}