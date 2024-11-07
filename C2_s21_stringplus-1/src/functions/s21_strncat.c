#include "../s21_string.h"

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  char* ptr = dest;
  // доходим до конца строки
  while (*dest) {
    dest++;
  }
  // присоединяем к строке n-символов строки src
  for (s21_size_t i = 0; i < n && *src; i++, src++) {
    *dest = *src;
    dest++;
  }
  *dest = '\0';
  return ptr;
}