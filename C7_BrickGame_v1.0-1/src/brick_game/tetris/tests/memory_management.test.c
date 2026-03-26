#include "tests.h"

START_TEST(ALLOCATE_ARRAY) {
  int result = 0;
  int** arr = NULL;
  result = AllocateArray(&arr, 0, 1);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  result = AllocateArray(&arr, 1, 0);
  ck_assert_int_eq(result, RUNTIME_ERROR);
}

END_TEST

START_TEST(FREE_ARRAY) {
  int** arr = NULL;
  AllocateArray(&arr, 4, 4);
  FreeArray(arr, 0);
  ck_assert_ptr_nonnull(arr);
  FreeArray(arr, 4);
}

END_TEST

START_TEST(GAME_MEM_CLEAR) {
  GameInfo_t game_info = {0};
  figure_t current_figure = {0};
  figure_t next_figure = {0};
  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);
  AllocateArray(&(game_info.next), NEXT_FIGURE_ROWS, NEXT_FIGURE_COLS);
  AllocateArray(&(current_figure.matrix), 4, 4);
  AllocateArray(&(next_figure.matrix), 4, 4);

  ck_assert_ptr_nonnull(game_info.field);
  ck_assert_ptr_nonnull(game_info.next);
  ck_assert_ptr_nonnull(current_figure.matrix);
  ck_assert_ptr_nonnull(next_figure.matrix);

  FreeMemory(&game_info, &current_figure, &next_figure);

  ck_assert_ptr_null(game_info.field);
  ck_assert_ptr_null(game_info.next);
  ck_assert_ptr_null(current_figure.matrix);
  ck_assert_ptr_null(next_figure.matrix);
}

END_TEST
TCase* tcase_memory_management(void) {
  TCase* tcase = tcase_create("ALLOCATE_ARRAY");
  tcase_add_test(tcase, ALLOCATE_ARRAY);
  tcase_add_test(tcase, FREE_ARRAY);
  tcase_add_test(tcase, GAME_MEM_CLEAR);
  return tcase;
}