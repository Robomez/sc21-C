#include "test_s21_decimal.h"

START_TEST(big_shift_left_normal) {
  s21_big big = {{0, 1, 0, 0, 1, 0, 0}};
  s21_big test = {{0, 2, 0, 0, 2, 0, 0}};
  int result = s21_big_shift_left(&big);
  ck_assert_int_eq(result, 0);
  for (int i = 0; i <= NUMBER_BIG_FLAGS; i++) {
    ck_assert_uint_eq(big.bits[i], test.bits[i]);
  }
}
END_TEST

START_TEST(big_shift_left_harder) {
  s21_big big = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 1, 0, 0}};
  s21_big test = {{0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 3, 0, 0}};
  int result = s21_big_shift_left(&big);
  ck_assert_int_eq(result, 0);
  for (int i = 0; i <= NUMBER_BIG_FLAGS; i++) {
    ck_assert_uint_eq(big.bits[i], test.bits[i]);
  }
}
END_TEST

START_TEST(big_shift_left_overflow) {
  s21_big big = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                  0xffffffff, 0}};
  s21_big test = {{0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                   0xffffffff, 0}};
  int result = s21_big_shift_left(&big);
  ck_assert_int_eq(result, 1);
  for (int i = 0; i <= NUMBER_BIG_FLAGS; i++) {
    ck_assert_uint_eq(big.bits[i], test.bits[i]);
  }
}
END_TEST

START_TEST(big_shift_right_normal) {
  s21_big big = {{0, 2, 0, 0, 2, 0, 0}};
  s21_big test = {{0, 1, 0, 0, 1, 0, 0}};
  int result = s21_big_shift_right(&big);
  ck_assert_int_eq(result, 0);
  for (int i = 0; i <= NUMBER_BIG_FLAGS; i++) {
    ck_assert_uint_eq(big.bits[i], test.bits[i]);
  }
}
END_TEST

START_TEST(big_shift_right_harder) {
  s21_big big = {{1, 1, 1, 1, 1, 0, 0x80030000}};
  s21_big test = {
      {0x80000000, 0x80000000, 0x80000000, 0x80000000, 0, 0, 0x80030000}};
  int result = s21_big_shift_right(&big);
  ck_assert_int_eq(result, 1);
  for (int i = 0; i <= NUMBER_BIG_FLAGS; i++) {
    ck_assert_uint_eq(big.bits[i], test.bits[i]);
  }
}
END_TEST

START_TEST(decimal_shift_left_normal) {
  s21_decimal decimal = {{0, 1, 0, 0}};
  s21_decimal test = {{0, 2, 0, 0}};
  int result = s21_decimal_shift_left(&decimal);
  ck_assert_int_eq(result, 0);
  for (int i = 0; i <= NUMBER_FLAGS; i++) {
    ck_assert_uint_eq(decimal.bits[i], test.bits[i]);
  }
}
END_TEST

START_TEST(decimal_shift_left_harder) {
  s21_decimal decimal = {{0xffffffff, 0xffffffff, 1, 0}};
  s21_decimal test = {{0xfffffffe, 0xffffffff, 3, 0}};
  int result = s21_decimal_shift_left(&decimal);
  ck_assert_int_eq(result, 0);
  for (int i = 0; i <= NUMBER_FLAGS; i++) {
    ck_assert_uint_eq(decimal.bits[i], test.bits[i]);
  }
}
END_TEST

START_TEST(decimal_shift_left_overflow) {
  s21_decimal decimal = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal test = {{0xfffffffe, 0xffffffff, 0xffffffff, 0}};
  int result = s21_decimal_shift_left(&decimal);
  ck_assert_int_eq(result, 1);
  for (int i = 0; i <= NUMBER_FLAGS; i++) {
    ck_assert_uint_eq(decimal.bits[i], test.bits[i]);
  }
}
END_TEST

START_TEST(decimal_shift_right_normal) {
  s21_decimal decimal = {{0, 2, 2, 0}};
  s21_decimal test = {{0, 1, 1, 0}};
  int result = s21_decimal_shift_right(&decimal);
  ck_assert_int_eq(result, 0);
  for (int i = 0; i <= NUMBER_FLAGS; i++) {
    ck_assert_uint_eq(decimal.bits[i], test.bits[i]);
  }
}
END_TEST

START_TEST(decimal_shift_right_harder) {
  s21_decimal decimal = {{1, 1, 1, 0x80030000}};
  s21_decimal test = {{0x80000000, 0x80000000, 0, 0x80030000}};
  int result = s21_decimal_shift_right(&decimal);
  ck_assert_int_eq(result, 1);
  for (int i = 0; i <= NUMBER_FLAGS; i++) {
    ck_assert_uint_eq(decimal.bits[i], test.bits[i]);
  }
}
END_TEST

START_TEST(number_shift) {
  uint32_t number = 0xffffffff;
  int result = s21_number_shift_left(&number);
  ck_assert_int_eq(result, 1);
  ck_assert_uint_eq(number, 0xfffffffe);
  result = s21_number_shift_right(&number);
  ck_assert_int_eq(result, 0);
  ck_assert_uint_eq(number, 0x7fffffff);
  result = s21_number_shift_right(&number);
  ck_assert_int_eq(result, 1);
  ck_assert_uint_eq(number, 0x3fffffff);
}
END_TEST

Suite *suite_shift(void) {
  Suite *s = suite_create("suite_shift");
  TCase *tc = tcase_create("s21_shift");

  tcase_add_test(tc, big_shift_left_normal);
  tcase_add_test(tc, big_shift_left_harder);
  tcase_add_test(tc, big_shift_left_overflow);
  tcase_add_test(tc, big_shift_right_normal);
  tcase_add_test(tc, big_shift_right_harder);
  tcase_add_test(tc, decimal_shift_left_normal);
  tcase_add_test(tc, decimal_shift_left_harder);
  tcase_add_test(tc, decimal_shift_left_overflow);
  tcase_add_test(tc, decimal_shift_right_normal);
  tcase_add_test(tc, decimal_shift_right_harder);
  tcase_add_test(tc, number_shift);

  suite_add_tcase(s, tc);
  return s;
}
