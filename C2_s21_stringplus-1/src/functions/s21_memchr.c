#include "../s21_string.h"

void *s21_memchr(const void *s, int c, s21_size_t n) {
  const void *ptr = S21_NULL;
  for (s21_size_t i = 0; i < n; i++, s++)  // пока не пройдёт n циклов
  {
    if (*(char *)s == (unsigned char)c)  // если нашли нужный символ
    {
      ptr = s;  // приравниваем возвращаемое значение к текущему проверяемуму
                // адресу
      break;    // выходим из цикла
    }
  }
  return (void *)ptr;  // возвращаем значение
}