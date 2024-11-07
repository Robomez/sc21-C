#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (s21_size_t i = 0; i < n && *str1 && *str1 == *str2; str1++, str2++, i++)
    ;  // цикл до тех пока пока символ строки str1 равен
       // символу строки str2 и
  return *str1 - *str2;  // возвращение раницы между символами после цикла
}