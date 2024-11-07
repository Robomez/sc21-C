#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  char *str2 = S21_NULL;
  if (str) {
    str2 = (char *)malloc(sizeof(char) * (s21_strlen(str) + 1));
    for (s21_size_t i = 0; i < s21_strlen(str); i++) {
      if ('a' <= str[i] && str[i] <= 'z') {
        str2[i] = str[i] - 32;
      } else {
        str2[i] = str[i];
      }
    }
    // избавляемся от мусора в конце строки
    str2[s21_strlen(str)] = '\0';
  }
  return str2;
}