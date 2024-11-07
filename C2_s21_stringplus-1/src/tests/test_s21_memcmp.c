#include "test_s21_string.h"

START_TEST(same_string) {
  char *str1 = "abcdef";
  char *str2 = "abcdef";
  ck_assert_int_eq(s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
}
END_TEST

START_TEST(first_area_shorter) {
  char *str1 = "abcde";
  char *str2 = "abcdef";
  ck_assert_int_eq(s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
}
END_TEST

START_TEST(first_area_longer) {
  char *str1 = "abcdef";
  char *str2 = "abcde";
  ck_assert_int_eq(s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
}
END_TEST

START_TEST(compare_length_smaller) {
  char *str1 = "abcdef";
  char *str2 = "abcdef";
  ck_assert_int_eq(s21_memcmp(str1, str2, 3), memcmp(str1, str2, 3));
}
END_TEST

START_TEST(compare_zero_length) {
  char *str1 = "abcdef";
  char *str2 = "abcdef";
  ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
}
END_TEST

START_TEST(same_start_diff_end) {
  char *str1 = "abcdeX";
  char *str2 = "abcdeY";
  ck_assert_int_eq(s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
}
END_TEST

START_TEST(difference_middle) {
  char *str1 = "abcXef";
  char *str2 = "abcYef";
  ck_assert_int_eq(s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
}
END_TEST

START_TEST(compare_empty_strings) {
  char *str1 = "";
  char *str2 = "";
  ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
}
END_TEST

Suite *suite_s21_memcmp(void) {
  Suite *s = suite_create("suite_s21_memcmp");
  TCase *tc = tcase_create("s21_memcmp_core");

  tcase_add_test(tc, same_string);
  tcase_add_test(tc, first_area_shorter);
  tcase_add_test(tc, first_area_longer);
  tcase_add_test(tc, compare_length_smaller);
  tcase_add_test(tc, compare_zero_length);
  tcase_add_test(tc, same_start_diff_end);
  tcase_add_test(tc, difference_middle);
  tcase_add_test(tc, compare_empty_strings);

  suite_add_tcase(s, tc);
  return s;
}