#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t index) {
  s21_size_t src_len = s21_strlen(src);  // заменить на s21_strlen
  s21_size_t str_len = s21_strlen(str);  // заменить на s21_strlen
  void *ptr = S21_NULL;
  int result = 0;
  if (index > src_len)  // если индекс боьлше длинны исходной строки
  {
    result = 1;
  } else {
    char *res = (char *)malloc(src_len + str_len + 1);
    if (!res) {
      result = 1;
    }

    if (result == 0) {
      char temp[src_len - index + 1];  // создаём массив для временного хранения
                                       // строки после индекса
      for (s21_size_t i = index, temp_index = 0; src[i]; i++, temp_index++) {
        temp[temp_index] = src[i];
      }
      temp[src_len - index] = '\0';  // добавляем терминирующий ноль в конец
      for (s21_size_t i = 0; i < index; i++) {
        res[i] = src[i];  // записываем все символы до index в массив
      }
      for (s21_size_t i = index, str_index = 0; str[str_index];
           i++, str_index++) {
        res[i] = str[str_index];  // вставляем в массив символы, начиная с index
      }
      for (s21_size_t i = (index + str_len), temp_index = 0; temp[temp_index];
           i++, temp_index++) {
        res[i] = temp[temp_index];  // вставляем в массив сохранённую ранее
                                    // строку, после добавления строки str
      }
      res[src_len + str_len] =
          '\0';  // добавляем терминирующий ноль в конец массива
      ptr = res;  // присваиваем указателю адрес строки
    }
  }
  return (void *)ptr;
}
