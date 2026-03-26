#include "./tests.h"

START_TEST(START_STOP_GAME) {
  GameInfo_t game_info = {0};
  figure_t current_figure = {0};
  figure_t next_figure = {0};

  StartGame(&game_info, &current_figure, &next_figure);

  ck_assert_ptr_nonnull(game_info.field);
  ck_assert_ptr_nonnull(game_info.next);
  ck_assert_ptr_nonnull(current_figure.matrix);
  ck_assert_ptr_nonnull(next_figure.matrix);

  StopGame(&game_info, &current_figure, &next_figure);

  ck_assert_ptr_null(game_info.field);
  ck_assert_ptr_null(game_info.next);
  ck_assert_ptr_null(current_figure.matrix);
  ck_assert_ptr_null(next_figure.matrix);
}
END_TEST

TCase *tcase_start_stop_game(void) {
  TCase *tcase = tcase_create("START_STOP_GAME");
  tcase_add_test(tcase, START_STOP_GAME);
  return tcase;
}