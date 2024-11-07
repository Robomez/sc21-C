#include "test_s21_string.h"

START_TEST(easy_test) {
  char str1[50] = "This is the test string for s21_string";
  char std_dast[50] = {0};
  char s21_dast[50] = {0};
  ck_assert_str_eq(s21_memcpy(s21_dast, str1, strlen(str1) + 1),
                   memcpy(std_dast, str1, strlen(str1) + 1));
}
END_TEST

START_TEST(zero_bytes) {
  char str1[50] = "This is the test string for s21_string";
  char std_dast1[50] = {0};
  char s21_dast1[50] = {0};
  ck_assert_str_eq(s21_memcpy(s21_dast1, str1, 0), memcpy(std_dast1, str1, 0));
}
END_TEST

START_TEST(empty_array) {
  char str2[50] = "";
  char std_dast2[50] = {0};
  char s21_dast2[50] = {0};
  ck_assert_str_eq(s21_memcpy(s21_dast2, str2, strlen(str2)),
                   memcpy(std_dast2, str2, strlen(str2)));
}
END_TEST

START_TEST(large_volume) {
  char str3[1000];
  char std_dast3[1000] = {0};
  char s21_dast3[1000] = {0};
  for (int i = 0; i < 1000; i++) str3[i] = (char)(i % 256);
  s21_memcpy(s21_dast3, str3, 1000);
  memcpy(std_dast3, str3, 1000);
  ck_assert_mem_eq(s21_dast3, std_dast3, 1000);
}
END_TEST

START_TEST(partial_string) {
  char str1[50] = "This is the test string for s21_string";
  char std_dast4[50] = {0};
  char s21_dast4[50] = {0};
  s21_memcpy(s21_dast4, str1, 5);
  memcpy(std_dast4, str1, 5);
  ck_assert_str_eq(std_dast4, s21_dast4);
}
END_TEST

START_TEST(copy_to_itself) {
  char std_dast6[50] = "This is string to string";
  char s21_dast6[50] = "This is string to string";
  s21_memcpy(s21_dast6 + 10, s21_dast6, 10);
  memcpy(std_dast6 + 10, std_dast6, 10);
  ck_assert_str_eq(std_dast6, s21_dast6);
}
END_TEST

Suite *suite_s21_memcpy(void) {
  Suite *s = suite_create("suite_s21_memcpy");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, easy_test);
  tcase_add_test(tc, zero_bytes);
  tcase_add_test(tc, empty_array);
  tcase_add_test(tc, large_volume);
  tcase_add_test(tc, partial_string);
  tcase_add_test(tc, copy_to_itself);

  suite_add_tcase(s, tc);
  return s;
}