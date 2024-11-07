#include "../s21_string.h"
// by deannecu

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = 0;   // переменая для длины
  const char *c1, *c2;  // указатели для строк которые будем сравнивать
  // пока разыменованый указатель(певый символ) ! = \0 потом смещаем указатель
  // на один
  int breaker = 0;
  for (c1 = str1; *c1 != '\0' && breaker == 0; c1++) {
    for (c2 = str2; *c2 != '\0' && breaker == 0; c2++) {
      // сравниваем разыменованые указатели
      if (*c1 == *c2) breaker = 1;
    }
    // увеличиваем счетчик если не равны
    if (breaker == 0) len++;
  }
  return len;
}