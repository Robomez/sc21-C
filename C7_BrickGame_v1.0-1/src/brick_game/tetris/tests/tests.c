#include "tests.h"

#define CK_DEFAULT_TIMEOUT 100000;

Suite *make_s21_tetris_suite(void);
TCase *tcase_create_figure(void);
TCase *tcase_copy_matrix(void);
TCase *tcase_rotate(void);
TCase *tcase_generate_next(void);

TCase *tcase_memory_management(void);

TCase *tcase_moving(void);
TCase *tcase_start_stop_game(void);
TCase *tcase_spawning(void);

TCase *tcase_game_info(void);
TCase *tcase_high_score(void);

TCase *tcase_timer(void);

TCase *user_input(void);

Suite *make_s21_tetris_suite() {
  Suite *suite = suite_create("TESTING - s21_tetris.a");

  suite_add_tcase(suite, tcase_copy_matrix());
  suite_add_tcase(suite, tcase_create_figure());
  suite_add_tcase(suite, tcase_rotate());
  suite_add_tcase(suite, tcase_generate_next());

  suite_add_tcase(suite, tcase_memory_management());

  suite_add_tcase(suite, tcase_moving());
  suite_add_tcase(suite, tcase_start_stop_game());
  suite_add_tcase(suite, tcase_spawning());

  suite_add_tcase(suite, tcase_game_info());
  suite_add_tcase(suite, tcase_high_score());

  suite_add_tcase(suite, tcase_timer());

  suite_add_tcase(suite, user_input());

  return suite;
}

int main(void) {
  int number_failed = 0;
  Suite *suite = make_s21_tetris_suite();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
