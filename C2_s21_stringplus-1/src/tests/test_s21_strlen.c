#include "test_s21_string.h"

START_TEST(zero) {
  char *test = "";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST

START_TEST(text) {
  char *test = "Another one bites the dust";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST

Suite *suite_s21_strlen(void) {
  Suite *s = suite_create("suite_s21_strlen");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, zero);
  tcase_add_test(tc, text);

  suite_add_tcase(s, tc);
  return s;
}