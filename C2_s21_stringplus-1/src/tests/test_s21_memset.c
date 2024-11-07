#include "test_s21_string.h"

START_TEST(fill_normal) {
  int arr1[100];
  int arr2[100];
  // Заполняем первый массив с помощью s21_memset()
  ck_assert_ptr_eq(s21_memset(arr1, 0, sizeof(arr1)), arr1);
  // Заполняем второй массив с помощью стандартной memset()
  ck_assert_ptr_eq(memset(arr2, 0, sizeof(arr2)), arr2);
  // Сравниваем содержимое массивов
  ck_assert_mem_eq(arr1, arr2, sizeof(arr1));
}
END_TEST

START_TEST(fill_letter) {
  int arr1[100];
  int arr2[100];
  // Заполняем первый массив с помощью s21_memset()
  ck_assert_ptr_eq(s21_memset(arr1, 'a', sizeof(arr1)), arr1);
  // Заполняем второй массив с помощью стандартной memset()
  ck_assert_ptr_eq(memset(arr2, 'a', sizeof(arr2)), arr2);
  // Сравниваем содержимое массивов
  ck_assert_mem_eq(arr1, arr2, sizeof(arr1));
}
END_TEST

START_TEST(fill_half) {
  int arr1[100];
  int arr2[100];
  ck_assert_ptr_eq(s21_memset(arr1, 0, sizeof(arr1) / 2), arr1);
  ck_assert_ptr_eq(memset(arr2, 0, sizeof(arr2) / 2), arr2);
  ck_assert_mem_eq(arr1, arr2, sizeof(arr1) / 2);
}
END_TEST

START_TEST(fill_zero_length) {
  int arr1[0];
  int arr2[0];
  ck_assert_ptr_eq(s21_memset(arr1, 0, sizeof(arr1)), arr1);
  ck_assert_ptr_eq(memset(arr2, 0, sizeof(arr2)), arr2);
  ck_assert_mem_eq(arr1, arr2, sizeof(arr1));
}
END_TEST

Suite *suite_s21_memset(void) {
  Suite *s = suite_create("suite_s21_memset");
  TCase *tc = tcase_create("s21_memset_core");

  tcase_add_test(tc, fill_normal);
  tcase_add_test(tc, fill_letter);
  tcase_add_test(tc, fill_half);
  tcase_add_test(tc, fill_zero_length);

  suite_add_tcase(s, tc);
  return s;
}