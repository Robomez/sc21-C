#include "test_s21_string.h"

START_TEST(normal) {
  char dest[100] = "Hello ";
  char src[] = "world!";
  char *res1 = s21_strncat(dest, src, 5);
  char *res2 = s21_strncat(dest, src, 5);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(empty_src) {
  char dest[100] = "Hello ";
  char src[] = "";
  char *res1 = s21_strncat(dest, src, 3);
  char *res2 = s21_strncat(dest, src, 3);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(zero_n) {
  char dest[100] = "Hello ";
  char src[] = "world!";
  char *res1 = s21_strncat(dest, src, 0);
  char *res2 = s21_strncat(dest, src, 0);
  ck_assert_str_eq(res1, res2);
}
END_TEST

Suite *suite_s21_strncat(void) {
  Suite *s = suite_create("suite_s21_strncat");
  TCase *tc = tcase_create("s21_strncat_core");

  tcase_add_test(tc, normal);
  tcase_add_test(tc, empty_src);
  tcase_add_test(tc, zero_n);

  suite_add_tcase(s, tc);
  return s;
}