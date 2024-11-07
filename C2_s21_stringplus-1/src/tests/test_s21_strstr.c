#include "test_s21_string.h"

START_TEST(easy_test) {
  char str1[50] = "This is the test string for s21_string";
  char *accept = "test";
  ck_assert_ptr_eq(s21_strstr(str1, accept), strstr(str1, accept));
}
END_TEST

START_TEST(space_test) {
  char str1[50] = "This is the test string for s21_string";
  char *accept = "test string";
  ck_assert_ptr_eq(s21_strstr(str1, accept), strstr(str1, accept));
}
END_TEST

START_TEST(ros_test) {
  char str1[50] = "This is the test string for рус s21_string";
  char *accept = "рус";
  ck_assert_ptr_eq(s21_strstr(str1, accept), strstr(str1, accept));
}
END_TEST

START_TEST(find_in_empty) {
  char str1[50] = "";
  char *accept = "hipo";
  ck_assert_ptr_eq(s21_strstr(str1, accept), strstr(str1, accept));
}
END_TEST

START_TEST(find_empty) {
  char str1[50] = "This is the test string for s21_string";
  char *accept = "";
  ck_assert_ptr_eq(s21_strstr(str1, accept), strstr(str1, accept));
}
END_TEST

Suite *suite_s21_strstr(void) {
  Suite *s = suite_create("suite_s21_strstr");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, easy_test);
  tcase_add_test(tc, space_test);
  tcase_add_test(tc, ros_test);
  tcase_add_test(tc, find_in_empty);
  tcase_add_test(tc, find_empty);

  suite_add_tcase(s, tc);
  return s;
}