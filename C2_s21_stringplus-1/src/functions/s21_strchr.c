#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;
  while (*str != '\0' && result == S21_NULL) {
    if (*str == c) {
      result = (char *)str;
    }
    str++;
  }
  return result;
}
