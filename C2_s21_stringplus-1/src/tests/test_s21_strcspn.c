#include "test_s21_string.h"

START_TEST(find_in_mid) {
  char string[] = "We are the champions";
  char letters[] = "er";
  ck_assert_uint_eq(strcspn(string, letters), s21_strcspn(string, letters));
}
END_TEST

START_TEST(find_in_empty) {
  char string[] = "";
  char letters[] = "er";
  ck_assert_uint_eq(strcspn(string, letters), s21_strcspn(string, letters));
}
END_TEST

START_TEST(find_empty) {
  char string[] = "We are the champions";
  char letters[] = "";
  ck_assert_uint_eq(strcspn(string, letters), s21_strcspn(string, letters));
}
END_TEST

Suite *suite_s21_strcspn(void) {
  Suite *s = suite_create("suite_s21_strcspn");
  TCase *tc = tcase_create("s21_strchr_core");

  tcase_add_test(tc, find_in_mid);
  tcase_add_test(tc, find_in_empty);
  tcase_add_test(tc, find_empty);

  suite_add_tcase(s, tc);
  return s;
}