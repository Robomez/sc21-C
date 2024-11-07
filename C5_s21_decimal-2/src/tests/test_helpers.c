#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "test_s21_decimal.h"

START_TEST(helpers) {
  s21_decimal decok = {{0, 0x80000000, 0, 0}};
  int oke = s21_decimal_is_ok(decok);
  ck_assert_int_eq(oke, 1);

  s21_decimal decnotok = {{0, 0, 0, 0xFFFFFFFF}};
  oke = s21_decimal_is_ok(decnotok);
  ck_assert_int_eq(oke, 0);

  decnotok.bits[3] = 0x00000FFF;
  oke = s21_decimal_is_ok(decnotok);
  ck_assert_int_eq(oke, 0);

  decnotok.bits[3] = 0xaf000000;
  oke = s21_decimal_is_ok(decnotok);
  ck_assert_int_eq(oke, 0);

  decnotok.bits[3] = 0x00f00000;
  oke = s21_decimal_is_ok(decnotok);
  ck_assert_int_eq(oke, 0);

  s21_big bigok = s21_decimal_to_big(decok);

  s21_big biggus = {{0, 0, 5000, 0, 0, 0, 0}};
  s21_big_precision_set(&biggus, 4);

  s21_big_normalize(&bigok, &biggus);
  ck_assert_int_eq(s21_big_precision_get(bigok), 4);

  ck_assert_int_eq(bigok.bits[2], 5000);
  ck_assert_int_eq(bigok.bits[1], 0);

  s21_big_precision_set(&biggus, 3);
  s21_big_normalize(&bigok, &biggus);
  ck_assert_int_eq(s21_big_precision_get(biggus), 4);
}
END_TEST

START_TEST(big_to_decimal) {
  s21_big big1 = {{4, 5, 0, 0, 0, 0, 0}};
  s21_decimal decimal1 = {{0}};
  int chiko = s21_big_to_decimal(big1, &decimal1);
  s21_decimal test = {{4, 5, 0, 0}};
  ck_assert_int_eq(chiko, 0);
  for (int i = 0; i <= NUMBER_FLAGS; i++) {
    ck_assert_int_eq(decimal1.bits[i], test.bits[i]);
  }

  s21_big big2 = {{12345, 25, 0, 50, 0, 0, 4}};
  s21_decimal decimal2 = {{0}};
  chiko = s21_big_to_decimal(big2, &decimal2);
  ck_assert_int_eq(chiko, 1);

  s21_big_precision_set(&big2, 4);
  chiko = s21_big_to_decimal(big2, &decimal2);
  ck_assert_int_eq(chiko, 0);
  s21_decimal test2 = {{1073741947, 0, 2147483648, 131072}};
  for (int i = 0; i <= NUMBER_FLAGS; i++) {
    ck_assert_int_eq(decimal2.bits[i], test2.bits[i]);
  }

  s21_big_to_zero(&big2);
  for (int i = 0; i <= NUMBER_BIG_FLAGS; i++) {
    ck_assert_int_eq(big2.bits[i], 0);
  }
}

Suite *suite_helpers(void) {
  Suite *s = suite_create("suite_helpers");
  TCase *tc = tcase_create("s21_helpers");

  tcase_add_test(tc, helpers);
  tcase_add_test(tc, big_to_decimal);

  suite_add_tcase(s, tc);
  return s;
}
