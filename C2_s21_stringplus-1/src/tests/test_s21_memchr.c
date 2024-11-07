#include "test_s21_string.h"

START_TEST(find_in_mid) {
  char str[] = "Hello, World!";
  int find_c = 'W';
  int len = strlen(str);
  ck_assert_ptr_eq(s21_memchr(str, find_c, len), memchr(str, find_c, len));
}
END_TEST
START_TEST(find_in_start) {
  char str[] = "Hello, World!";
  int find_c = 'H';
  int len = strlen(str);
  ck_assert_ptr_eq(s21_memchr(str, find_c, len), memchr(str, find_c, len));
}
END_TEST
START_TEST(find_in_end) {
  char str[] = "Hello, World!";
  int find_c = '!';
  int len = strlen(str);
  ck_assert_ptr_eq(s21_memchr(str, find_c, len), memchr(str, find_c, len));
}
END_TEST
START_TEST(find_not_present) {
  char str[] = "Hello, World!";
  int find_c = 'a';
  int len = strlen(str);
  ck_assert_ptr_eq(s21_memchr(str, find_c, len), memchr(str, find_c, len));
}
END_TEST

START_TEST(find_null_terminator) {
  char str[] = "Hello, World!";
  int find_c = '\0';
  int len = strlen(str);
  ck_assert_ptr_eq(s21_memchr(str, find_c, len + 1),
                   memchr(str, find_c, len + 1));
}
END_TEST

START_TEST(find_in_empty_search_area) {
  char str[] = "Hello, World!";
  int find_c = 'W';
  int len = 0;
  ck_assert_ptr_eq(s21_memchr(str, find_c, len), memchr(str, find_c, len));
}
END_TEST

START_TEST(find_outoff_string) {
  char str1[20] = "Hello";
  int find_c = 'o';
  int len = 20;
  ck_assert_ptr_eq(s21_memchr(str1, find_c, len), memchr(str1, find_c, len));
}
END_TEST

Suite *suite_s21_memchr(void) {
  Suite *s = suite_create("suite_s21_memchr");
  TCase *tc = tcase_create("s21_memchr_core");

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