#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "test_s21_decimal.h"

START_TEST(mantissa_add) {
  s21_big b1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                 0xffffffff, 0}};
  s21_big b2 = {{1, 0, 0, 0, 0, 0, 0}};
  s21_big_mantissa_add(b1, b2);
}
END_TEST

START_TEST(mantissa_sub) {
  s21_big b1 = {
      {0xffffffff, 0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_big b2 = {{0xffffffff, 5, 0, 0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_big_mantissa_sub(b1, b2);
}
END_TEST

START_TEST(big_div10) {
  s21_big b1 = {{0, 50, 0, 0, 0, 0, 0x00020000}};
  int result = s21_big_div10(&b1);
  ck_assert_int_eq(b1.bits[1], 5);
  ck_assert_int_eq(result, 0);

  result = s21_big_div10(&b1);
  ck_assert_int_eq(b1.bits[1], 0);
  ck_assert_int_eq(b1.bits[0], 0x80000000);
  ck_assert_int_eq(result, 0);

  result = s21_big_div10(&b1);
  ck_assert_int_eq(b1.bits[1], 0);
  ck_assert_int_eq(b1.bits[0], 0x80000000);
  ck_assert_int_eq(result, -1);
}
END_TEST

Suite *suite_arith_help(void) {
  Suite *s = suite_create("suite_arith_help");
  TCase *tc = tcase_create("s21_arith_help");

  tcase_add_test(tc, mantissa_add);
  tcase_add_test(tc, mantissa_sub);
  tcase_add_test(tc, big_div10);

  suite_add_tcase(s, tc);
  return s;
}
