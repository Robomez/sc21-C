#include "test_s21_decimal.h"

START_TEST(big_precision_get) {
  s21_big big = {{0, 1, 0, 0, 1, 0, 0xffffffff}};
  int bit = s21_big_precision_get(big);
  ck_assert_int_eq(bit, 255);
}
END_TEST

START_TEST(big_precision_set) {
  s21_big big = {{0, 1, 0, 0, 1, 0, 0xffffffff}};
  s21_big_precision_set(&big, 0);
  int result = s21_big_precision_get(big);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(big_sign_get) {
  s21_big big = {{0, 1, 0, 0, 1, 0, 0xffffffff}};
  int bit = s21_big_sign_get(big);
  ck_assert_int_eq(bit, 1);
}
END_TEST

START_TEST(big_sign_set) {
  s21_big big = {{0, 1, 0, 0, 1, 0, 0xffffffff}};
  s21_big_sign_set(&big, 0);
  int result = s21_big_sign_get(big);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(bit_get) {
  s21_decimal decimal = {{0, 1, 0, 0}};
  int bit = s21_bit_get(decimal.bits[1], 0);
  ck_assert_int_eq(bit, 1);
}
END_TEST

START_TEST(bit_reverse) {
  s21_decimal decimal = {{0, 1, 0, 0}};
  s21_bit_reverse(&(decimal.bits[1]), 0);
  int bit = s21_bit_get(decimal.bits[1], 0);
  ck_assert_int_eq(bit, 0);
}
END_TEST

START_TEST(bit_set) {
  s21_decimal decimal = {{0, 1, 0, 0}};
  s21_bit_set(&(decimal.bits[1]), 0, 0);
  int bit = s21_bit_get(decimal.bits[1], 0);
  ck_assert_int_eq(bit, 0);

  s21_bit_set(&(decimal.bits[1]), 0, 1);
  bit = s21_bit_get(decimal.bits[1], 0);
  ck_assert_int_eq(bit, 1);
}
END_TEST

START_TEST(decimal_precision_get) {
  s21_decimal decimal = {{0, 1, 0, 0xffffffff}};
  int bit = s21_decimal_precision_get(decimal);
  ck_assert_int_eq(bit, 255);
}
END_TEST

START_TEST(decimal_precision_set) {
  s21_decimal decimal = {{0, 1, 0, 0xffffffff}};
  s21_decimal_precision_set(&decimal, 0);
  int result = s21_decimal_precision_get(decimal);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(decimal_sign_get) {
  s21_decimal decimal = {{0, 1, 0, 0xffffffff}};
  int bit = s21_decimal_sign_get(decimal);
  ck_assert_int_eq(bit, 1);
}
END_TEST

START_TEST(decimal_sign_set) {
  s21_decimal decimal = {{0, 1, 0, 0xffffffff}};
  s21_decimal_sign_set(&decimal, 0);
  int result = s21_decimal_sign_get(decimal);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *suite_getset(void) {
  Suite *s = suite_create("suite_getset");
  TCase *tc = tcase_create("s21_getset");

  tcase_add_test(tc, big_precision_get);
  tcase_add_test(tc, big_precision_set);
  tcase_add_test(tc, big_sign_get);
  tcase_add_test(tc, big_sign_set);
  tcase_add_test(tc, decimal_precision_get);
  tcase_add_test(tc, decimal_precision_set);
  tcase_add_test(tc, decimal_sign_get);
  tcase_add_test(tc, decimal_sign_set);
  tcase_add_test(tc, bit_get);
  tcase_add_test(tc, bit_set);
  tcase_add_test(tc, bit_reverse);

  suite_add_tcase(s, tc);
  return s;
}
