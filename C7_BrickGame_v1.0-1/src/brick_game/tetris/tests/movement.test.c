#include "tests.h"

START_TEST(MOVE_LEFT) {
  GameInfo_t game_info = {0};
  figure_t figure = {0};
  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);

  InitFigure(figureI, &figure);
  figure.ul_row = 0;
  figure.ul_col = 2;
  MoveHorizontal(DirectionLeft, &game_info, &figure);
  ck_assert_int_eq(game_info.field[0][2], 0);
  ck_assert_int_eq(game_info.field[0][1], FIELD_SIGN_FIGURE);

  MoveHorizontal(DirectionLeft, &game_info, &figure);
  ck_assert_int_eq(game_info.field[0][1], 0);
  ck_assert_int_eq(game_info.field[0][0], FIELD_SIGN_FIGURE);

  MoveHorizontal(DirectionLeft, &game_info, &figure);
  ck_assert_int_eq(game_info.field[0][0], FIELD_SIGN_FIGURE);

  FreeArray(game_info.field, FIELD_HEIGHT);
  FreeArray(figure.matrix, 4);
}

START_TEST(MOVE_LEFT_RIGHT_COLLISION) {
  GameInfo_t game_info = {0};
  figure_t figure = {0};
  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);

  InitFigure(figureI, &figure);
  figure.ul_row = 0;
  figure.ul_col = 2;

  game_info.field[0][figure.ul_col - 1] = 1;
  game_info.field[0][figure.ul_col + figure.cols] = 1;

  for (int i = 0; i < figure.rows; i++) {
    for (int j = 0; j < figure.cols; j++) {
      game_info.field[i][j + figure.ul_col] += figure.matrix[i][j];
    }
  }

  ck_assert_int_eq(game_info.field[0][2], FIELD_SIGN_FIGURE);

  MoveHorizontal(DirectionLeft, &game_info, &figure);
  ck_assert_int_eq(game_info.field[0][2], FIELD_SIGN_FIGURE);
  ck_assert_int_eq(game_info.field[0][1], 1);

  MoveHorizontal(DirectionRight, &game_info, &figure);
  ck_assert_int_eq(game_info.field[0][figure.ul_col + figure.cols - 1],
                   FIELD_SIGN_FIGURE);
  ck_assert_int_eq(game_info.field[0][figure.ul_col + figure.cols], 1);

  FreeArray(game_info.field, FIELD_HEIGHT);
  FreeArray(figure.matrix, 4);
}

END_TEST

START_TEST(MOVE_RIGHT) {
  GameInfo_t game_info = {0};
  figure_t figure = {0};
  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);

  InitFigure(figureI, &figure);
  figure.ul_row = 0;
  int init_col = FIELD_WIDTH - figure.cols - 2;
  figure.ul_col = init_col;
  MoveHorizontal(DirectionRight, &game_info, &figure);
  ck_assert_int_eq(game_info.field[0][init_col], 0);
  ck_assert_int_eq(game_info.field[0][init_col + 1], FIELD_SIGN_FIGURE);

  MoveHorizontal(DirectionRight, &game_info, &figure);
  ck_assert_int_eq(game_info.field[0][init_col + 1], 0);
  ck_assert_int_eq(game_info.field[0][init_col + 2], FIELD_SIGN_FIGURE);

  MoveHorizontal(DirectionRight, &game_info, &figure);
  ck_assert_int_eq(game_info.field[0][FIELD_WIDTH - 1], FIELD_SIGN_FIGURE);

  FreeArray(game_info.field, FIELD_HEIGHT);
  FreeArray(figure.matrix, 4);
}

START_TEST(MOVE_DOWN) {
  GameInfo_t game_info = {0};
  figure_t figure = {0};
  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);

  InitFigure(figureI, &figure);
  int init_row = 0;
  int init_col = 5;
  figure.ul_row = init_row;
  figure.ul_col = init_col;

  MoveDown(&game_info, &figure);
  ck_assert_int_eq(game_info.field[init_row][init_col], 0);
  init_row++;
  ck_assert_int_eq(game_info.field[init_row + 1][init_col], FIELD_SIGN_FIGURE);

  MoveDown(&game_info, &figure);
  ck_assert_int_eq(game_info.field[init_row][init_col], 0);
  init_row++;
  ck_assert_int_eq(game_info.field[init_row + 1][init_col], FIELD_SIGN_FIGURE);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    MoveDown(&game_info, &figure);
  }
  ck_assert_int_eq(game_info.field[FIELD_HEIGHT - 1][init_col],
                   FIELD_SIGN_FIGURE);

  FreeArray(game_info.field, FIELD_HEIGHT);
  FreeArray(figure.matrix, 4);
}

START_TEST(DROP_DOWN) {
  GameInfo_t game_info = {0};
  figure_t figure = {0};
  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);
  InitFigure(figureI, &figure);

  Drop(&game_info, &figure);

  for (int i = figure.ul_row; i < figure.rows; i++) {
    for (int j = figure.ul_col; j < figure.cols; j++) {
      ck_assert_int_eq(game_info.field[i][j],
                       figure.matrix[i - figure.ul_row][j - figure.ul_col]);
    }
  }

  FreeArray(game_info.field, FIELD_HEIGHT);
  FreeArray(figure.matrix, 4);
}
END_TEST

START_TEST(MOVE_DOWN_COLLISION) {
  GameInfo_t game_info = {0};
  figure_t figure = {0};
  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);

  InitFigure(figureI, &figure);
  int init_row = 0;
  int init_col = 5;
  figure.ul_row = init_row;
  figure.ul_col = init_col;

  game_info.field[init_row + figure.rows][init_col] = 1;

  for (int i = 0; i < figure.rows; i++) {
    for (int j = 0; j < figure.cols; j++) {
      game_info.field[init_row + i][init_col + j] += figure.matrix[i][j];
    }
  }
  MoveDown(&game_info, &figure);
  ck_assert_int_eq(game_info.field[init_row + figure.rows][init_col], 1);
  ck_assert_int_eq(game_info.field[init_row][init_col], FIELD_SIGN_FIGURE);

  FreeArray(game_info.field, FIELD_HEIGHT);
  FreeArray(figure.matrix, 4);
}

START_TEST(MOVE_FAILING) {
  int result = 0;
  figure_t figure = {0};
  GameInfo_t game_info = {0};

  result = MoveDown((GameInfo_t*)NULL, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  game_info.field = (int**)1;
  result = MoveDown(&game_info, (figure_t*)NULL);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  game_info.field = NULL;
  result = MoveDown(&game_info, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  game_info.field = (int**)1;
  figure.matrix = NULL;
  result = MoveDown(&game_info, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  result = MoveHorizontal(DirectionLeft, (GameInfo_t*)NULL, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  result = MoveHorizontal(DirectionRight, (GameInfo_t*)NULL, &figure);
  ck_assert_int_eq(result, RUNTIME_ERROR);
}

TCase* tcase_moving(void) {
  TCase* tcase = tcase_create("MOVEMENT");
  tcase_add_test(tcase, MOVE_LEFT);
  tcase_add_test(tcase, MOVE_RIGHT);
  tcase_add_test(tcase, MOVE_LEFT_RIGHT_COLLISION);
  tcase_add_test(tcase, MOVE_DOWN);
  tcase_add_test(tcase, DROP_DOWN);
  tcase_add_test(tcase, MOVE_DOWN_COLLISION);
  tcase_add_test(tcase, MOVE_FAILING);

  return tcase;
}