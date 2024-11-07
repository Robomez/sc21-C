#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  s21_size_t src_len = s21_strlen(src);

  while (i < n) {
    if (i < src_len) {
      dest[i] = src[i];
      i++;
    } else {
      dest[i] = '\0';
      i++;
    }
  }

  return dest;
}