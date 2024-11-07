#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *ptr_str1 = (unsigned char *)str1;
  unsigned char *ptr_str2 = (unsigned char *)str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (*ptr_str1 != *ptr_str2) return *ptr_str1 - *ptr_str2;
    ptr_str1++;
    ptr_str2++;
  }
  return 0;
}