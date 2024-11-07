#include "test_s21_string.h"

START_TEST(middle) {
  char src[50] = "Hello world";
  char *str = " goddamn ";
  char *res = "Hello goddamn  world";
  char *check = s21_insert(src, str, 5);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(start) {
  char src[50] = "Hello world";
  char *str = " goddamn ";
  char *res = " goddamn Hello world";
  char *check = s21_insert(src, str, 0);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(end) {
  char src[50] = "Hello world";
  char *str = " goddamn ";
  char *res = "Hello world goddamn ";
  char *check = s21_insert(src, str, 11);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(to_empty) {
  char src[50] = "";
  char *str = " goddamn ";
  char *res = " goddamn ";
  char *check = s21_insert(src, str, 0);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(empty) {
  char src[50] = "Hello world";
  char *str = "";
  char *res = "Hello world";
  char *check = s21_insert(src, str, 0);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(rnd) {
  char *src = "0123456789";
  char *str = "hello";
  char *res = S21_NULL;
  char *check = s21_insert(src, str, 15);
  ck_assert_ptr_eq(check, res);
  if (check) free(check);
}
END_TEST

Suite *suite_s21_insert(void) {
  Suite *s = suite_create("suite_s21_insert");
  TCase *tc = tcase_create("s21_insert_core");

  tcase_add_test(tc, middle);
  tcase_add_test(tc, start);
  tcase_add_test(tc, end);
  tcase_add_test(tc, to_empty);
  tcase_add_test(tc, empty);
  tcase_add_test(tc, rnd);

  suite_add_tcase(s, tc);
  return s;
}