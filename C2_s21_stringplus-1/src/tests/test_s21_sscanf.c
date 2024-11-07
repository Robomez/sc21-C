#include "test_s21_string.h"
// int test
START_TEST(test_int) {
  char *str = "!123";
  int s21_n = 0;
  int std_n = 0;
  s21_sscanf(str, "!%d", &s21_n);
  sscanf(str, "!%d", &std_n);

  ck_assert_int_eq(s21_n, std_n);
  // if (res) free(res);
}
END_TEST

// uint test
START_TEST(test_uint) {
  char *str = "123";
  unsigned int s21_n = 0;
  unsigned int std_n = 0;
  s21_sscanf(str, "%u", &s21_n);
  sscanf(str, "%u", &std_n);

  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

// float test
START_TEST(test_float) {
  char *str = "123.456";
  float s21_n = 0;
  float std_n = 0;
  s21_sscanf(str, "%f", &s21_n);
  sscanf(str, "%f", &std_n);

  ck_assert_double_eq(s21_n, std_n);
}
END_TEST

// char test
START_TEST(test_char) {
  char *str = "a";
  char s21_n = 0;
  char std_n = 0;
  s21_sscanf(str, "%c", &s21_n);
  sscanf(str, "%c", &std_n);

  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

// chars test
START_TEST(test_chars) {
  char *str = "aaa";
  char s21_n = 0;
  char std_n = 0;
  s21_sscanf(str, "%c", &s21_n);
  sscanf(str, "%c", &std_n);

  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

// str test
START_TEST(test_str) {
  char *str = "aaa";
  char s21_n[100];
  char std_n[100];
  s21_sscanf(str, "%s", s21_n);
  sscanf(str, "%s", std_n);

  ck_assert_str_eq(s21_n, std_n);
}
END_TEST

// hex test
START_TEST(test_hex) {
  char *str = "1A2F 0ff3";
  unsigned int s21_n, s212;
  unsigned int std_n, s2;
  s21_sscanf(str, "%x %X", &s21_n, &s212);
  sscanf(str, "%x %X", &std_n, &s2);

  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

// width test
START_TEST(test_width) {
  char *str = " abcdefghijklmnopqrstu 4";
  char s21_n[100];
  char std_n[100];
  int num, num2;
  sscanf(str, " %10s %d", std_n, &num2);
  s21_sscanf(str, " %10s %d", s21_n, &num);

  ck_assert_str_eq(s21_n, std_n);
}
END_TEST

// %i test
START_TEST(test_decimal) {
  char *str = "123";
  int s21_n = 0;
  int std_n = 0;
  s21_sscanf(str, "%i", &s21_n);
  sscanf(str, "%i", &std_n);

  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

// octa test
START_TEST(test_octa) {
  char *str = "012";
  unsigned int s21_n;
  unsigned int std_n;
  s21_sscanf(str, "%o", &s21_n);
  sscanf(str, "%o", &std_n);

  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

// ptr test
START_TEST(test_ptr) {
  char *str = "0x7fffad6b6049";
  void *s21_n = S21_NULL;
  void *std_n = S21_NULL;
  s21_sscanf(str, "%p", &s21_n);
  sscanf(str, "%p", &std_n);

  ck_assert_ptr_eq(s21_n, std_n);
}
END_TEST

// n test
START_TEST(test_n) {
  char *str = "012sdd";
  unsigned int s21_n;
  unsigned int std_n;
  char arr[100];
  char arr2[100];
  s21_sscanf(str, "%s%n", arr, &s21_n);
  sscanf(str, "%s%n", arr2, &std_n);

  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

// prnct test
START_TEST(test_prnct) {
  char *str = "d %%";
  char s21_n;
  char std_n;
  s21_sscanf(str, "%c %% ", &s21_n);
  sscanf(str, "%c %% ", &std_n);

  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

// suppress test
START_TEST(test_suppress) {
  char *str = "5 2";
  unsigned int s21_n;
  unsigned int std_n;
  s21_sscanf(str, "%*d%d", &s21_n);
  sscanf(str, "%*d%d", &std_n);

  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

// h test
START_TEST(test_h) {
  char *str = "32768";
  short int s21_n;
  short int std_n;
  s21_sscanf(str, "%hd", &s21_n);
  sscanf(str, "%hd", &std_n);

  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

// l test
START_TEST(test_l) {
  char *str = "9223372036854775808";
  long int s21_n;
  long int std_n;
  s21_sscanf(str, "%ld", &s21_n);
  sscanf(str, "%ld", &std_n);

  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

// L test
START_TEST(test_L) {
  char *str = "125123512551231525124e-19";
  long double s21_n;
  long double std_n;
  s21_sscanf(str, "%Lf", &s21_n);
  sscanf(str, "%Lf", &std_n);

  ck_assert_ldouble_eq(s21_n, std_n);
}
END_TEST

// L test
START_TEST(test_other) {
  char *str = "125123512551231525124e-19 3.1415 -2.717 1.34e+5";
  float s21_n, s212, s213, s214;
  float std_n, s2, s3, s4;
  s21_sscanf(str, "%e %E %g %G", &s21_n, &s212, &s213, &s214);
  sscanf(str, "%e %E %g %G", &std_n, &s2, &s3, &s4);

  ck_assert_ldouble_eq(s21_n, std_n);
}
END_TEST

Suite *suite_s21_sscanf(void) {
  Suite *s = suite_create("suite_s21_sscanf");
  TCase *tc = tcase_create("s21_sscanf_core");

  tcase_add_test(tc, test_int);
  tcase_add_test(tc, test_uint);
  tcase_add_test(tc, test_float);
  tcase_add_test(tc, test_char);
  tcase_add_test(tc, test_chars);
  tcase_add_test(tc, test_str);
  tcase_add_test(tc, test_hex);
  tcase_add_test(tc, test_width);
  tcase_add_test(tc, test_decimal);
  tcase_add_test(tc, test_octa);
  tcase_add_test(tc, test_ptr);
  tcase_add_test(tc, test_n);
  tcase_add_test(tc, test_prnct);
  tcase_add_test(tc, test_suppress);
  tcase_add_test(tc, test_h);
  tcase_add_test(tc, test_l);
  tcase_add_test(tc, test_L);
  tcase_add_test(tc, test_other);

  suite_add_tcase(s, tc);
  return s;
}