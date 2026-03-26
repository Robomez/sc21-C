#include "tests.h"

START_TEST(ROTATE_FIGURE) {
  int expected[4][4] = {
      {12, 8, 4, 0},   //
      {13, 9, 5, 1},   //
      {14, 10, 6, 2},  //
      {15, 11, 7, 3},  //
  };

  figure_t figure = {0};
  InitFigure(figureI, &figure);

  figure.cols = 4;
  figure.rows = 4;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure.matrix[i][j] = i * 4 + j;
    }
  }

  Rotate(&figure);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(figure.matrix[i][j], expected[i][j]);
    }
  }
  FreeArray(figure.matrix, 4);
}

START_TEST(ROTATE_FAILING) {
  int result = 0;
  result = Rotate((figure_t*)NULL);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  figure_t figure = {0};
  figure.matrix = NULL;
  result = Rotate((&figure));
  ck_assert_int_eq(result, RUNTIME_ERROR);
}

START_TEST(ROTATE_FIGURE_I) {
  const int X = FIELD_SIGN_FIGURE;
  int expected[4][4] = {
      {X, X, X, X},  //
      {0, 0, 0, 0},  //
      {0, 0, 0, 0},  //
      {0, 0, 0, 0},  //
  };

  figure_t figure_I = {0};
  InitFigure(figureI, &figure_I);

  Rotate(&figure_I);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(figure_I.matrix[i][j], expected[i][j]);
    }
  }
  FreeArray(figure_I.matrix, 4);
}

END_TEST

START_TEST(ROTATE_FIGURE_L) {
  const int X = FIELD_SIGN_FIGURE;
  int expected[4][4] = {
      {X, X, X, 0},  //
      {X, 0, 0, 0},  //
      {0, 0, 0, 0},  //
      {0, 0, 0, 0},  //
  };

  figure_t figure_L = {0};
  InitFigure(2, &figure_L);

  Rotate(&figure_L);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(figure_L.matrix[i][j], expected[i][j]);
    }
  }
  FreeArray(figure_L.matrix, 4);
}

START_TEST(WITHOUT_COLLISION) {
  const int X = FIELD_SIGN_FIGURE;
  int expected[4][4] = {
      {X, 0, 0, 0},  //
      {X, 0, 0, 0},  //
      {X, 0, 0, 0},  //
      {X, 0, 0, 0},  //
  };

  figure_t figure = {0};
  InitFigure(figureI, &figure);
  Rotate(&figure);
  figure.ul_row = 15;
  figure.ul_col = 0;

  GameInfo_t game_info = {0};
  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);

  for (int i = figure.ul_row; i < figure.ul_row + figure.rows; i++) {
    for (int j = figure.ul_col; j < figure.ul_col + figure.cols; j++) {
      game_info.field[i][j] =
          figure.matrix[i - figure.ul_row][j - figure.ul_col];
    }
  }
  int result = RotateInField(&game_info, &figure);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(game_info.field[figure.ul_row + i][j], expected[i][j]);
    }
  }
  ck_assert_int_eq(result, 0);

  FreeArray(game_info.field, FIELD_HEIGHT);
  FreeArray(figure.matrix, 4);
}

START_TEST(WITH_COLLISION) {
  const int X = FIELD_SIGN_FIGURE;
  int expected[4][4] = {
      {X, X, X, X},  //
      {0, 0, 0, 0},  //
      {0, 0, 0, 0},  //
      {1, 0, 0, 0},  //
  };

  figure_t figure = {0};
  InitFigure(figureI, &figure);
  Rotate(&figure);
  figure.ul_row = 16;
  figure.ul_col = 0;

  GameInfo_t game_info = {0};
  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game_info.field[figure.ul_row + i][j] = expected[i][j];
    }
  }

  int result = RotateInField(&game_info, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(game_info.field[figure.ul_row + i][j], expected[i][j]);
    }
  }

  FreeArray(game_info.field, FIELD_HEIGHT);
  FreeArray(figure.matrix, 4);
}

START_TEST(OUT_OF_FIELD) {
  int result = 0;

  figure_t figure = {0};
  InitFigure(figureI, &figure);
  figure.ul_row = 0;
  figure.ul_col = 7;

  GameInfo_t game_info = {0};
  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);

  PositionFigure(game_info.field, &figure);

  result = RotateInField(&game_info, &figure);

  ck_assert_int_eq(result, 0);
  for (int j = FIELD_WIDTH - figure.cols; j < FIELD_WIDTH; j++) {
    ck_assert_int_eq(game_info.field[figure.ul_row][j], FIELD_SIGN_FIGURE);
  }

  figure.ul_row = 17;
  figure.ul_col = 0;
  const int X = FIELD_SIGN_FIGURE;

  int expected[4][4] = {
      {X, X, X, X},  //
      {0, 0, 0, 0},  //
      {0, 0, 0, 0},  //
      {0, 0, 0, 0},  //
  };

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figure.ul_row + i < FIELD_HEIGHT) {
        game_info.field[figure.ul_row + i][j] = expected[i][j];
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figure.ul_row + i < FIELD_HEIGHT) {
        ck_assert_int_eq(game_info.field[figure.ul_row + i][j], expected[i][j]);
      }
    }
  }

  result = RotateInField(&game_info, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  FreeArray(game_info.field, FIELD_HEIGHT);
  FreeArray(figure.matrix, 4);
}

END_TEST

START_TEST(WITH_FAILING) {
  int result = 0;
  figure_t figure = {0};
  GameInfo_t game_info = {0};

  result = RotateInField((GameInfo_t*)NULL, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  game_info.field = (int**)1;
  result = RotateInField(&game_info, (figure_t*)NULL);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  game_info.field = NULL;
  result = RotateInField(&game_info, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  game_info.field = (int**)1;
  figure.matrix = NULL;
  result = RotateInField(&game_info, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);
}
END_TEST

TCase* tcase_rotate(void) {
  TCase* tcase = tcase_create("ROTATION");
  tcase_add_test(tcase, ROTATE_FIGURE);
  tcase_add_test(tcase, ROTATE_FAILING);
  tcase_add_test(tcase, ROTATE_FIGURE_I);
  tcase_add_test(tcase, ROTATE_FIGURE_L);
  tcase_add_test(tcase, WITHOUT_COLLISION);
  tcase_add_test(tcase, WITH_COLLISION);
  tcase_add_test(tcase, OUT_OF_FIELD);
  tcase_add_test(tcase, WITH_FAILING);
  return tcase;
}