#include "../s21_string.h"

// Цикл на n-раз, каждую иттерацию байт заменяется на
// значение unsigned char c
// Как и в оригинальной функции - можно получить
// ошибку в случае, когда n > sizeof(arr)
void* s21_memset(void* str, int c, s21_size_t n) {
  void* ptr = str;
  for (s21_size_t i = 0; i < n; i++, str++) {
    *(char*)str = (unsigned char)c;
  }
  return ptr;
}
