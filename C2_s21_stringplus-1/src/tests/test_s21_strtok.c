#include "test_s21_string.h"

START_TEST(easy_test) {
  char str1[50] = "apple,banana|cherry.date+elderberry";
  char str2[50] = "apple,banana|cherry.date+elderberry";
  char *delim = "|+,";
  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);
  ck_assert_str_eq(token1, token2);
  while (token1 != S21_NULL && token2 != S21_NULL) {
    token1 = s21_strtok(S21_NULL, delim);
    token2 = strtok(S21_NULL, delim);
    if (token1 != S21_NULL && token2 != S21_NULL) {
      ck_assert_str_eq(token1, token2);
    }
  }
}
END_TEST

START_TEST(find_in_empty_test) {
  char str1[50] = "";
  char *delim = "|+,";
  ck_assert_ptr_eq(s21_strtok(str1, delim), strtok(str1, delim));
}
END_TEST

START_TEST(find_empty_test) {
  char str1[50] = "apple,banana|cherry.date+elderberry";
  char *delim = "";
  ck_assert_ptr_eq(s21_strtok(str1, delim), strtok(str1, delim));
}
END_TEST

START_TEST(trim_test) {
  char str1[50] = ",,,,apple,banana|cherry.date+elderberry||||";
  char str2[50] = ",,,,apple,banana|cherry.date+elderberry||||";
  char *delim = "|+,";
  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);
  ck_assert_str_eq(token1, token2);

  while (token1 != S21_NULL && token2 != S21_NULL) {
    token1 = s21_strtok(S21_NULL, delim);
    token2 = strtok(S21_NULL, delim);
    if (token1 != S21_NULL && token2 != S21_NULL) {
      ck_assert_str_eq(token1, token2);
    }
  }
}
END_TEST

START_TEST(multiple_calls_test) {
  char str1[50] = "apple,banana|cherry.date+elderberry";
  char str2[50] = "apple,banana|cherry.date+elderberry";
  char *delim = "|+,";
  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);
  ck_assert_str_eq(token1, token2);

  while (token1 != S21_NULL && token2 != S21_NULL) {
    token1 = s21_strtok(S21_NULL, delim);
    token2 = strtok(S21_NULL, delim);
    if (token1 != S21_NULL && token2 != S21_NULL) {
      ck_assert_str_eq(token1, token2);
    }
  }
}
END_TEST

START_TEST(restart_tokenization_test) {
  char str1[50] = "apple,banana|cherry.date+elderberry";
  char *delim = "|+,";
  s21_strtok(str1, delim);
  strtok(str1, delim);

  char str2[50] = "grape|kiwi";
  char *token1 = s21_strtok(str2, delim);
  char *token2 = strtok(str2, delim);
  ck_assert_str_eq(token1, token2);
}
END_TEST

Suite *suite_s21_strtok(void) {
  Suite *s = suite_create("suite_s21_strtok");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, easy_test);
  tcase_add_test(tc, find_in_empty_test);
  tcase_add_test(tc, find_empty_test);
  tcase_add_test(tc, trim_test);
  tcase_add_test(tc, multiple_calls_test);
  tcase_add_test(tc, restart_tokenization_test);

  suite_add_tcase(s, tc);
  return s;
}