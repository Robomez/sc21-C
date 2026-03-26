#include "tests.h"

START_TEST(GENERATE_NEXT) {
  figure_t figure = {0};

  for (int i = 0; i < 100; i++) {
    int result = GenerateNextFigure(&figure);

    ck_assert_int_ge(result / 10, 0);
    ck_assert_int_le(result / 10, 6);
    ck_assert_int_ge(result % 10, 0);
    ck_assert_int_le(result % 10, 3);
  }

  FreeArray(figure.matrix, 4);
}

END_TEST

TCase* tcase_generate_next(void) {
  TCase* tcase = tcase_create("GENERATE_NEXT");
  tcase_add_test(tcase, GENERATE_NEXT);
  return tcase;
}