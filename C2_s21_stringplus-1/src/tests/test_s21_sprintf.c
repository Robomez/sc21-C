#include "test_s21_string.h"

// тест для строки
START_TEST(test_string) {
  char str1[100] = "";
  char str2[100] = "";
  int res1, res2;
  res1 = s21_sprintf(str1, "String: %s", "Hello, World!");
  res2 = sprintf(str2, "String: %s", "Hello, World!");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для целого числа
START_TEST(test_integer) {
  char str1[50] = "";
  char str2[50] = "";
  int res1, res2;
  res1 = s21_sprintf(str1, "Integer: %d %i", 12345, -15);
  res2 = sprintf(str2, "Integer: %d %i", 12345, -15);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для целого числа флаг I
START_TEST(test_integer_I) {
  char str1[50] = "";
  char str2[50] = "";
  int res1, res2;
  long number = 12345;
  res1 = s21_sprintf(str1, "Integer: %ld", number);
  res2 = sprintf(str2, "Integer: %ld", number);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для целого числа со знаком
START_TEST(test_signed_integer) {
  char str1[50] = "";
  char str2[50] = "";
  int res1, res2;
  res1 = s21_sprintf(str1, "Signed Integer: %+d %+d", -12345, 0);
  res2 = sprintf(str2, "Signed Integer: %+d %+d", -12345, 0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для беззнакового целого числа
START_TEST(test_unsigned) {
  char str1[50] = "";
  char str2[50] = "";
  int res1, res2;
  res1 = s21_sprintf(str1, "Unsigned: %u", 12345U);
  res2 = sprintf(str2, "Unsigned: %u", 12345U);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для числа с плавающей точкой
START_TEST(test_float1) {
  char str1[500] = "";
  char str2[500] = "";
  int res1, res2;
  double f = 123.45678910;
  res1 = s21_sprintf(str1, "Float: %.2f %+10f %-10f %+10f %-10f %05f", f, f, -f,
                     -f, f, f);
  res2 = sprintf(str2, "Float: %.2f %+10f %-10f %+10f %-10f %05f", f, f, -f, -f,
                 f, f);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для числа с плавающей точкой
START_TEST(test_float2) {
  char str1[500] = "";
  char str2[500] = "";
  int res1, res2;
  double f = 123.45678910;
  res1 = s21_sprintf(str1, "Float: %20f %-20f %.0f % 0f %05f", f, f, f, f, f);
  res2 = sprintf(str2, "Float: %20f %-20f %.0f % 0f %05f", f, f, f, f, f);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для числа с плавающей точкой
START_TEST(test_float3) {
  char str1[500] = "";
  char str2[500] = "";
  double f = 555.25;
  long double lf = 3.14159265358979323846;
  int res1, res2;
  res1 = s21_sprintf(str1, "%.1f %.2f %Lf %016f %*.*f", f, f, lf, f, 6, 6, f);
  res2 = sprintf(str2, "%.1f %.2f %Lf %016f %*.*f", f, f, lf, f, 6, 6, f);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для символа процента
START_TEST(test_percent) {
  char str1[50] = "";
  char str2[50] = "";
  int res1, res2;
  res1 = s21_sprintf(str1, "Percent: %%");
  res2 = sprintf(str2, "Percent: %%");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для флагов
START_TEST(test_flags) {
  char str1[100] = "";
  char str2[100] = "";
  int res1, res2;
  res1 = s21_sprintf(str1, "Flags: %+d, % d", 123, 456);
  res2 = sprintf(str2, "Flags: %+d, % d", 123, 456);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для ширины и точности
START_TEST(test_width_precision) {
  char str1[100] = "";
  char str2[100] = "";
  int res1, res2;
  res1 = s21_sprintf(str1, "Width: %10d, Precision: %.5d", 123, 456);
  res2 = sprintf(str2, "Width: %10d, Precision: %.5d", 123, 456);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для коротких целых чисел
START_TEST(test_short_integer) {
  char str1[50] = "";
  char str2[50] = "";
  short int num = 12345;
  int res1, res2;
  res1 = s21_sprintf(str1, "Short: %hd", num);
  res2 = sprintf(str2, "Short: %hd", num);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для длинных целых чисел
START_TEST(test_long_integer) {
  char str1[50] = "";
  char str2[50] = "";
  long int num = 1234567890L;
  int res1, res2;
  res1 = s21_sprintf(str1, "Long: %ld", num);
  res2 = sprintf(str2, "Long: %ld", num);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для длинных беззнаковых целых чисел
START_TEST(test_unsigned_long) {
  char str1[50] = "";
  char str2[50] = "";
  unsigned long int num = 1234567890UL;
  int res1, res2;
  res1 = s21_sprintf(str1, "Unsigned Long: %lu", num);
  res2 = sprintf(str2, "Unsigned Long: %lu", num);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для строки с шириной и точностью
START_TEST(test_string_width_precision) {
  char str1[100] = "";
  char str2[100] = "";
  int res1, res2;
  res1 = s21_sprintf(str1, "String: %10.5s", "Hello, World!");
  res2 = sprintf(str2, "String: %10.5s", "Hello, World!");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для ширины больше длины числа
START_TEST(test_width_greater_than_length) {
  char str1[100] = "";
  char str2[100] = "";
  int res1, res2;
  res1 = s21_sprintf(str1, "Width greater: %10d", 42);
  res2 = sprintf(str2, "Width greater: %10d", 42);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для числа с минимальной шириной и без флагов
START_TEST(test_minimum_width_no_flags) {
  char str1[100] = "";
  char str2[100] = "";
  int res1, res2;
  res1 = s21_sprintf(str1, "%5d", 42);
  res2 = sprintf(str2, "%5d", 42);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// тест для символа
START_TEST(test_character) {
  char str1[50] = "";
  char str2[50] = "";
  int res1, res2;
  res1 = s21_sprintf(str1, "Char: %c", 'X');
  res2 = sprintf(str2, "Char: %c", 'X');
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_i) {
  char str1[50] = "";
  char str2[50] = "";
  int res1, res2;
  short num1 = -12345;
  long num2 = -123456789;
  res1 = s21_sprintf(str1, "Short %hi Long %li %06i", num1, num2, num1);
  res2 = sprintf(str2, "Short %hi Long %li %06i", num1, num2, num1);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_left_integer) {
  char str1[50] = "";
  char str2[50] = "";
  int res1, res2;
  int num = 12345;

  res1 = s21_sprintf(str1, "Left Aligned Integer: %-5i", num);
  res2 = sprintf(str2, "Left Aligned Integer: %-5i", num);

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_simple_text) {
  char str1[50] = "";
  char str2[50] = "";
  int res1, res2;

  res1 = s21_sprintf(str1, "simple text");
  res2 = sprintf(str2, "simple text");

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_l) {
  char str1[50] = "";
  char str2[50] = "";
  wchar_t *text = L"привет";
  wchar_t letter = L'ч';

  s21_sprintf(str1, "%ls%lc", text, letter);
  sprintf(str2, "%ls%lc", text, letter);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_wrong_specifier) {
  char str1[50] = "";

  s21_sprintf(str1, "simple text %p @");
}
END_TEST

START_TEST(test_hex) {
  char str1[50] = "";
  char str2[50] = "";
  int i = 255;

  s21_sprintf(str1, "%x %#x %-4x %.4x %o %06o", i, i, i, i, i, i);
  sprintf(str2, "%x %#x %-4x %.4x %o %06o", i, i, i, i, i, i);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_heX) {
  char str1[50] = "";
  char str2[50] = "";
  int i = 255;

  s21_sprintf(str1, "%X %#X %-4X %.4X", i, i, i, i);
  sprintf(str2, "%X %#X %-4X %.4X", i, i, i, i);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_n) {
  char str1[50] = "";
  char str2[50] = "";
  int i = 255;
  int s21n = 0;
  int n = 0;

  s21_sprintf(str1, "%X %n ag %n", i, &s21n, &s21n);
  sprintf(str2, "%X %n ag %n", i, &n, &n);

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21n, n);
}
END_TEST

Suite *suite_s21_sprintf(void) {
  Suite *s = suite_create("suite_s21_sprintf");
  TCase *tc = tcase_create("s21_sprintf_core");

  tcase_add_test(tc, test_string);
  tcase_add_test(tc, test_integer);
  tcase_add_test(tc, test_signed_integer);
  tcase_add_test(tc, test_unsigned);
  tcase_add_test(tc, test_float1);
  tcase_add_test(tc, test_float2);
  tcase_add_test(tc, test_float3);
  tcase_add_test(tc, test_percent);
  tcase_add_test(tc, test_flags);
  tcase_add_test(tc, test_width_precision);
  tcase_add_test(tc, test_short_integer);
  tcase_add_test(tc, test_long_integer);
  tcase_add_test(tc, test_unsigned_long);
  tcase_add_test(tc, test_string_width_precision);
  tcase_add_test(tc, test_width_greater_than_length);
  tcase_add_test(tc, test_minimum_width_no_flags);
  tcase_add_test(tc, test_character);
  tcase_add_test(tc, test_integer_I);
  tcase_add_test(tc, test_i);
  tcase_add_test(tc, test_l);
  tcase_add_test(tc, test_left_integer);
  tcase_add_test(tc, test_simple_text);
  tcase_add_test(tc, test_wrong_specifier);
  tcase_add_test(tc, test_hex);
  tcase_add_test(tc, test_heX);
  tcase_add_test(tc, test_n);

  suite_add_tcase(s, tc);
  return s;
}