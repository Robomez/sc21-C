#include <check.h>

#include "./tests/test_s21_decimal.h"

int main() {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(suite_getset());
  srunner_add_suite(sr, suite_print());
  srunner_add_suite(sr, suite_shift());
  srunner_add_suite(sr, suite_helpers());
  srunner_add_suite(sr, suite_arith_help());
  srunner_add_suite(sr, suite_s21_arithmetics());
  srunner_add_suite(sr, suite_s21_compare());
  srunner_add_suite(sr, suite_s21_convertors());
  srunner_add_suite(sr, suite_s21_others());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
