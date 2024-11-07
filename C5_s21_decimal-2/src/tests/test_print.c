#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "test_s21_decimal.h"

START_TEST(print) {
  // Сохранить оригинальный stdout
  int original_stdout = dup(STDOUT_FILENO);
  // Открыть /dev/null и перенаправить stdout на него
  int dev_null = open("/dev/null", O_WRONLY);
  dup2(dev_null, STDOUT_FILENO);
  close(dev_null);

  s21_decimal decimal = {{0, 1, 0, 0x00050000}};
  s21_big big = s21_decimal_to_big(decimal);
  uint32_t number = decimal.bits[3];
  s21_big_print_binary(big);
  s21_big_print_denary(big);
  s21_big_print_hex(big);
  s21_big_print_hex_oneline(big);
  s21_decimal_print_binary(decimal);
  s21_decimal_print_denary(decimal);
  s21_decimal_print_hex(decimal);
  s21_decimal_print_hex_oneline(decimal);
  s21_number_print_binary(number);
  s21_number_print_denary(number);
  s21_number_print_hex(number);

  // Восстановить оригинальный stdout
  dup2(original_stdout, STDOUT_FILENO);
  close(original_stdout);
}
END_TEST

Suite *suite_print(void) {
  Suite *s = suite_create("suite_print");
  TCase *tc = tcase_create("s21_print");

  tcase_add_test(tc, print);

  suite_add_tcase(s, tc);
  return s;
}
