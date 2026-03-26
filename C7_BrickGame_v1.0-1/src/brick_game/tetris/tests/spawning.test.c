#include "tests.h"

START_TEST(SPAWNING) {
  GameInfo_t game_info = {0};
  figure_t figure = {0};
  figure_t next_figure = {0};

  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);
  AllocateArray(&(game_info.next), 4, 4);
  InitFigure(figureI, &next_figure);
  InitFigure(figureI, &figure);

  int next_col = next_figure.ul_col;
  int next_cols = next_figure.cols;
  int next_rows = next_figure.rows;
  int matrix[4][4];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix[i][j] = next_figure.matrix[i][j];
    }
  }

  int result = SpawnFigure(&game_info, &figure, &next_figure);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(figure.ul_col, next_col);
  ck_assert_int_eq(figure.rows, next_rows);
  ck_assert_int_eq(figure.cols, next_cols);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(matrix[i][j], figure.matrix[i][j]);
    }
  }

  FreeArray(game_info.field, FIELD_HEIGHT);
  FreeArray(game_info.next, 4);
  FreeArray(next_figure.matrix, 4);
  FreeArray(figure.matrix, 4);
}

START_TEST(SPAWNING_WITH_COLLISION) {
  GameInfo_t game_info = {0};
  figure_t figure = {0};
  figure_t next_figure = {0};

  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);
  AllocateArray(&(game_info.next), 4, 4);

  InitFigure(figureO, &next_figure);
  next_figure.ul_col = 0;

  InitFigure(figureI, &figure);

  game_info.field[0][0] = 1;

  int result = SpawnFigure(&game_info, &figure, &next_figure);
  ck_assert_int_ne(result, 0);

  FreeArray(game_info.field, FIELD_HEIGHT);
  FreeArray(game_info.next, 4);
  FreeArray(next_figure.matrix, 4);
  FreeArray(figure.matrix, 4);
}
END_TEST

TCase* tcase_spawning(void) {
  TCase* tcase = tcase_create("SPAWNING");
  tcase_add_test(tcase, SPAWNING);
  tcase_add_test(tcase, SPAWNING_WITH_COLLISION);
  return tcase;
}