#include <check.h>

#include "./tests/test_s21_matrix.h"

int main() {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(suite_create_matrix());
  srunner_add_suite(sr, suite_remove_matrix());
  srunner_add_suite(sr, suite_eq_matrix());
  srunner_add_suite(sr, suite_sum_matrix());
  srunner_add_suite(sr, suite_sub_matrix());
  srunner_add_suite(sr, suite_mult_number());
  srunner_add_suite(sr, suite_mult_matrix());
  srunner_add_suite(sr, suite_transpose());
  srunner_add_suite(sr, suite_determinant());
  srunner_add_suite(sr, suite_calc_complements());
  srunner_add_suite(sr, suite_inverse_matrix());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
