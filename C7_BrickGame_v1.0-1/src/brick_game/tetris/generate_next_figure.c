/**
 * @file generate_next_figure.c
 * @brief Функции для генерации следующей фигуры.
 */

#include "./backend_internal.h"

/**
 * @brief Генерирует случайную фигуру, определяет её начальное положение и
 * вращение.
 *
 * Эта функция случайным образом выбирает один из 7 типов фигур и присваивает ее
 * указанной структуре. Она также устанавливает начальные координаты фигуры
 * в верхней части игрового поля, центрируя её по горизонтали. Дополнительно,
 * фигура случайным образом поворачивается до 3 раз.
 *
 * @param figure Указатель на структуру `figure_t` для хранения сгенерированной
 * фигуры.
 * @return Составное значение типа `int`, которое представляет собой
 * комбинацию идентификатора фигуры (`figure_id`) и количества поворотов
 * (`times_rotated`). Возвращаемое значение вычисляется по формуле:
 * `figure_id * 10 + times_rotated`.
 */
int GenerateNextFigure(figure_t *figure) {
  int figure_id = rand() % (FIGURE_COUNT);
  int times_rotated = rand() % 4;

  InitFigure(figure_id, figure);
  figure->ul_row = 0;
  figure->ul_col = FIELD_WIDTH / 2 - figure->cols / 2;

  for (int i = 0; i < times_rotated; i++) Rotate(figure);
  return figure_id * 10 + times_rotated;
}