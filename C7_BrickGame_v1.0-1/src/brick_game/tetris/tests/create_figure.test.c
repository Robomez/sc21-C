#include "tests.h"

START_TEST(CREATE_FIGURE) {
  figure_t figure = {0};

  AllocateArray(&(figure.matrix), 4, 4);

  InitFigure(figureI, &figure);

  ck_assert_int_eq(figure.ul_row, 0);
  ck_assert_int_eq(figure.ul_col, 0);
  ck_assert_int_eq(figure.rows, 4);
  ck_assert_int_eq(figure.cols, 1);

  const int X = FIELD_SIGN_FIGURE;
  int template[4][4] = {
      {X, 0, 0, 0},  //
      {X, 0, 0, 0},  //
      {X, 0, 0, 0},  //
      {X, 0, 0, 0}   //
  };

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(figure.matrix[i][j], template[i][j]);
    }
  }

  FreeArray(figure.matrix, 4);
}

START_TEST(CREATE_FIGURE_FAIL) {
  figure_t figure = {0};

  int result = 0;
  result = InitFigure(RUNTIME_ERROR, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);
  result = InitFigure(7, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);
  result = InitFigure(7, NULL);
  ck_assert_int_eq(result, RUNTIME_ERROR);
  FreeArray(figure.matrix, 4);

  result = InitFigure(figureI, &figure);
  ck_assert_int_eq(result, 0);
  FreeArray(figure.matrix, 4);
}

END_TEST

TCase* tcase_create_figure(void) {
  TCase* tcase = tcase_create("CREATE_FIGURE");
  tcase_add_test(tcase, CREATE_FIGURE);
  tcase_add_test(tcase, CREATE_FIGURE_FAIL);
  return tcase;
}