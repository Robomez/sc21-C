#include "test_s21_string.h"

START_TEST(all_low) {
  char *src = "hello world";
  char *res = "HELLO WORLD";
  char *check = s21_to_upper(src);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(all_up) {
  char *src = "HELLO WORLD";
  char *res = "HELLO WORLD";
  char *check = s21_to_upper(src);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(one_start_up) {
  char *src = "Hello world";
  char *res = "HELLO WORLD";
  char *check = s21_to_upper(src);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(same_start_up) {
  char *src = "HELlo world";
  char *res = "HELLO WORLD";
  char *check = s21_to_upper(src);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(one_end_up) {
  char *src = "hello worlD";
  char *res = "HELLO WORLD";
  char *check = s21_to_upper(src);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(same_end_up) {
  char *src = "hello woRLD";
  char *res = "HELLO WORLD";
  char *check = s21_to_upper(src);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(one_middle_up) {
  char *src = "hellO world";
  char *res = "HELLO WORLD";
  char *check = s21_to_upper(src);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(same_middle_up) {
  char *src = "heLLO WOrld";
  char *res = "HELLO WORLD";
  char *check = s21_to_upper(src);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(with_number) {
  char *src = "hello world123";
  char *res = "HELLO WORLD123";
  char *check = s21_to_upper(src);
  ck_assert_str_eq(check, res);
  if (check) free(check);
}
END_TEST

START_TEST(null) {
  char *src = S21_NULL;
  char *check = s21_to_upper(src);
  ck_assert_ptr_eq(check, S21_NULL);
  if (check) free(check);
}
END_TEST

Suite *suite_s21_to_upper(void) {
  Suite *s = suite_create("suite_s21_to_upper");
  TCase *tc = tcase_create("s21_to_upper_core");

  tcase_add_test(tc, all_low);
  tcase_add_test(tc, all_up);
  tcase_add_test(tc, one_start_up);
  tcase_add_test(tc, same_start_up);
  tcase_add_test(tc, one_end_up);
  tcase_add_test(tc, same_end_up);
  tcase_add_test(tc, one_middle_up);
  tcase_add_test(tc, same_middle_up);
  tcase_add_test(tc, with_number);
  tcase_add_test(tc, null);

  suite_add_tcase(s, tc);
  return s;
}