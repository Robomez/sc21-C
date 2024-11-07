#include "test_s21_string.h"

START_TEST(normal) {
  char *src = "123Hello world123";
  char *chars = "123";
  char *check = "Hello world";
  char *res = s21_trim(src, chars);

  ck_assert_str_eq(res, check);
  if (res) free(res);
}
END_TEST

START_TEST(end) {
  char *src = "Hello world123";
  char *chars = "123";
  char *check = "Hello world";
  char *res = s21_trim(src, chars);

  ck_assert_str_eq(res, check);
  if (res) free(res);
}
END_TEST

START_TEST(start) {
  char *src = "123Hello world";
  char *chars = "123";
  char *check = "Hello world";
  char *res = s21_trim(src, chars);

  ck_assert_str_eq(res, check);
  if (res) free(res);
}
END_TEST

START_TEST(from_empty) {
  char *src = "";
  char *chars = "123";
  char *check = "";
  char *res = s21_trim(src, chars);

  ck_assert_str_eq(res, check);
  if (res) free(res);
}
END_TEST

START_TEST(empty) {
  char *src = "123Hello world123";
  char *chars = "";
  char *check = "123Hello world123";
  char *res = s21_trim(src, chars);

  ck_assert_str_eq(res, check);
  if (res) free(res);
}
END_TEST

START_TEST(from_null) {
  char *src = S21_NULL;
  char *chars = "123";

  ck_assert_ptr_eq(s21_trim(src, chars), S21_NULL);
}
END_TEST

START_TEST(null) {
  char *src = "123Hello world123";
  char *chars = S21_NULL;

  ck_assert_ptr_eq(s21_trim(src, chars), S21_NULL);
}
END_TEST

START_TEST(rnd) {
  char *src = "123Hello world123";
  char *chars = "Hello";
  char *check = "123Hello world123";
  char *res = s21_trim(src, chars);

  ck_assert_str_eq(res, check);
  if (res) free(res);
}
END_TEST

START_TEST(equal) {
  char *src = "123Hello world123";
  char *chars = "123Hello world123";
  char *check = "";
  char *res = s21_trim(src, chars);

  ck_assert_str_eq(res, check);
  if (res) free(res);
}
END_TEST

Suite *suite_s21_trim(void) {
  Suite *s = suite_create("suite_s21_trim");
  TCase *tc = tcase_create("s21_trim_core");

  tcase_add_test(tc, normal);
  tcase_add_test(tc, end);
  tcase_add_test(tc, start);
  tcase_add_test(tc, from_empty);
  tcase_add_test(tc, empty);
  tcase_add_test(tc, from_null);
  tcase_add_test(tc, null);
  tcase_add_test(tc, rnd);
  tcase_add_test(tc, equal);

  suite_add_tcase(s, tc);
  return s;
}