#include "test_s21_decimal.h"

START_TEST(is_equal) {
  s21_decimal deca = {{0, 1, 1, 0}};
  s21_decimal decb = {{0, 1, 1, 0}};

  ck_assert_int_eq(s21_is_equal(decb, deca), 1);

  s21_decimal_sign_set(&decb, 1);
  ck_assert_int_eq(s21_is_equal(decb, deca), 0);

  s21_decimal_sign_set(&decb, 0);
  deca.bits[0] = 12;
  ck_assert_int_eq(s21_is_equal(decb, deca), 0);

  s21_decimal decc = {{0, 0, 0, 0}};
  s21_decimal decd = {{0, 0, 0, 0}};
  s21_decimal_precision_set(&decc, 16);
  s21_decimal_sign_set(&decd, 1);
  ck_assert_int_eq(s21_is_equal(decc, decd), 1);
}
END_TEST

START_TEST(is_not_equal) {
  s21_decimal deca = {{0, 1, 1, 0}};
  s21_decimal decb = {{0, 1, 1, 0}};

  ck_assert_int_eq(s21_is_not_equal(decb, deca), 0);

  s21_decimal_sign_set(&decb, 1);
  ck_assert_int_eq(s21_is_not_equal(decb, deca), 1);

  s21_decimal_sign_set(&decb, 0);
  deca.bits[0] = 12;
  ck_assert_int_eq(s21_is_not_equal(decb, deca), 1);
}
END_TEST

START_TEST(is_greater) {
  s21_decimal deca = {{0, 1, 1, 0}};
  s21_decimal decb = {{0, 2, 2, 0}};
  s21_decimal_precision_set(&deca, 5);
  ck_assert_int_eq(s21_is_greater(deca, decb), 0);
  ck_assert_int_eq(s21_is_greater(decb, deca), 1);

  s21_decimal_sign_set(&decb, 1);
  ck_assert_int_eq(s21_is_greater(deca, decb), 1);
  ck_assert_int_eq(s21_is_greater(decb, deca), 0);

  s21_decimal_sign_set(&deca, 1);
  ck_assert_int_eq(s21_is_greater(deca, decb), 1);
  ck_assert_int_eq(s21_is_greater(decb, deca), 0);
}
END_TEST

START_TEST(is_less) {
  s21_decimal deca = {{0, 1, 1, 0}};
  s21_decimal decb = {{0, 2, 2, 0}};
  s21_decimal_precision_set(&deca, 5);
  ck_assert_int_eq(s21_is_less(deca, decb), 1);
  ck_assert_int_eq(s21_is_less(decb, deca), 0);

  s21_decimal_sign_set(&decb, 1);
  ck_assert_int_eq(s21_is_less(deca, decb), 0);
  ck_assert_int_eq(s21_is_less(decb, deca), 1);

  s21_decimal_sign_set(&deca, 1);
  ck_assert_int_eq(s21_is_less(deca, decb), 0);
  ck_assert_int_eq(s21_is_less(decb, deca), 1);
}
END_TEST

START_TEST(is_greater_or_equal) {
  s21_decimal deca = {{0, 1, 1, 0}};
  s21_decimal decb = {{0, 2, 2, 0}};
  s21_decimal_precision_set(&deca, 5);
  ck_assert_int_eq(s21_is_greater_or_equal(deca, decb), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(decb, deca), 1);

  s21_decimal_sign_set(&decb, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(deca, decb), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(decb, deca), 0);

  s21_decimal_sign_set(&deca, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(deca, decb), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(decb, deca), 0);

  s21_decimal_precision_set(&deca, 0);
  deca.bits[1] = 2;
  deca.bits[2] = 2;
  ck_assert_int_eq(s21_is_greater_or_equal(deca, decb), 1);
}
END_TEST

START_TEST(is_less_or_equal) {
  s21_decimal deca = {{0, 1, 1, 0}};
  s21_decimal decb = {{0, 2, 2, 0}};
  s21_decimal_precision_set(&deca, 5);
  ck_assert_int_eq(s21_is_less_or_equal(deca, decb), 1);
  ck_assert_int_eq(s21_is_less_or_equal(decb, deca), 0);

  s21_decimal_sign_set(&decb, 1);
  ck_assert_int_eq(s21_is_less_or_equal(deca, decb), 0);
  ck_assert_int_eq(s21_is_less_or_equal(decb, deca), 1);

  s21_decimal_sign_set(&deca, 1);
  ck_assert_int_eq(s21_is_less_or_equal(deca, decb), 0);
  ck_assert_int_eq(s21_is_less_or_equal(decb, deca), 1);

  s21_decimal_precision_set(&deca, 0);
  deca.bits[1] = 2;
  deca.bits[2] = 2;
  ck_assert_int_eq(s21_is_less_or_equal(deca, decb), 1);
}
END_TEST

Suite *suite_s21_compare(void) {
  Suite *s = suite_create("suite_s21_compare");
  TCase *tc = tcase_create("s21_compare");

  tcase_add_test(tc, is_equal);
  tcase_add_test(tc, is_not_equal);
  tcase_add_test(tc, is_greater);
  tcase_add_test(tc, is_less);
  tcase_add_test(tc, is_greater_or_equal);
  tcase_add_test(tc, is_less_or_equal);

  suite_add_tcase(s, tc);
  return s;
}