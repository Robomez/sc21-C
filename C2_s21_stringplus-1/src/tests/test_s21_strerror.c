#include "test_s21_string.h"

START_TEST(zero) { ck_assert_str_eq(strerror(0), s21_strerror(0)); }
END_TEST

START_TEST(hundred_six) { ck_assert_str_eq(strerror(106), s21_strerror(106)); }
END_TEST

START_TEST(hunderd_seven) {
  ck_assert_str_eq(strerror(197), s21_strerror(197));
}
END_TEST

START_TEST(hundred_thirty_three) {
  ck_assert_str_eq(strerror(133), s21_strerror(133));
}
END_TEST

START_TEST(hundred_fifty) {
  ck_assert_str_eq(strerror(150), s21_strerror(150));
}
END_TEST

Suite *suite_s21_strerror(void) {
  Suite *s = suite_create("suite_s21_strerror");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, zero);
  tcase_add_test(tc, hundred_six);
  tcase_add_test(tc, hunderd_seven);
  tcase_add_test(tc, hundred_thirty_three);
  tcase_add_test(tc, hundred_fifty);

  suite_add_tcase(s, tc);
  return s;
}