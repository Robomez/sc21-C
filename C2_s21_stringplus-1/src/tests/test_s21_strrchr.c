#include "test_s21_string.h"

START_TEST(find_in_mid) {
  char str[] = "Hello, World!";
  int find_c = 'W';
  ck_assert_ptr_eq(s21_strrchr(str, find_c), strrchr(str, find_c));
}
END_TEST

START_TEST(find_in_start) {
  char str[] = "Hello, World!";
  int find_c = 'H';
  ck_assert_ptr_eq(s21_strrchr(str, find_c), strrchr(str, find_c));
}
END_TEST

START_TEST(find_in_end) {
  char str[] = "Hello, World!";
  int find_c = '!';
  ck_assert_ptr_eq(s21_strrchr(str, find_c), strrchr(str, find_c));
}
END_TEST

START_TEST(find_not_present) {
  char str[] = "Hello, World!";
  int find_c = 'a';
  ck_assert_ptr_eq(s21_strrchr(str, find_c), strrchr(str, find_c));
}
END_TEST

START_TEST(find_null_terminator) {
  char str[] = "Hello, World!";
  int find_c = '\0';
  ck_assert_ptr_eq(s21_strrchr(str, find_c + 1), strrchr(str, find_c + 1));
}
END_TEST

START_TEST(find_in_empty_search_area) {
  char str[] = "Hello, World!";
  int find_c = 'W';
  ck_assert_ptr_eq(s21_strrchr(str, find_c), strrchr(str, find_c));
}
END_TEST

START_TEST(find_outoff_string) {
  char str1[20] = "Hello";
  int find_c = 'o';
  ck_assert_ptr_eq(s21_strrchr(str1, find_c), strrchr(str1, find_c));
}
END_TEST

Suite *suite_s21_strrchr(void) {
  Suite *s = suite_create("suite_s21_strrchr");
  TCase *tc = tcase_create("s21_strrchr_core");

  tcase_add_test(tc, find_in_mid);
  tcase_add_test(tc, find_in_start);
  tcase_add_test(tc, find_in_end);
  tcase_add_test(tc, find_not_present);
  tcase_add_test(tc, find_null_terminator);
  tcase_add_test(tc, find_in_empty_search_area);
  tcase_add_test(tc, find_outoff_string);

  suite_add_tcase(s, tc);
  return s;
}