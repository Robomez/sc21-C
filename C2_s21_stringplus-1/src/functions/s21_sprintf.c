#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "../s21_string.h"

#define SUCCEED 0
#define ERROR -1

#define MINUS_FLAG 0b1
#define PLUS_FLAG 0b10
#define SPACE_FLAG 0b100
#define STAR_FLAG 0b1000
#define SHARP_FLAG 0b10000
#define ZERO_FLAG 0b100000

#define H_LENGHT_FLAG 0b1
#define L_LENGHT_FLAG 0b10
#define L_CAPS_LENGHT_FLAG 0b100
#define NO_CAPS_FLAG 0b1000

typedef enum specificators {
  C,
  F,
  S,
  PERCENT,
  I,
  U,
  D,
  E,
  G,
  e,
  g,
  X,
  x,
  O,
  P,
  N
} specificators;

int parse_specificator(const char **format_pointer, int *flags, int *width,
                       int *precision, int *length, specificators *specificator,
                       va_list);
int get_flags(const char **format_pointer, int *flags);
int get_width(const char **format_pointer, int *width, va_list);
int get_precision(const char **format_pointer, int *precision, va_list);
int get_length(const char **format_pointer, int *length);
int get_specificator(const char **format_pointer, specificators *specificator);
int is_flag(char c);
int is_digit(char c);
int is_specificator(char c);
int int_to_string(char **string_pointer, long long int number, int flags,
                  int width, int precision, int base);
int double_to_string(char **string_pointer, long double number, int flags,
                     int width, int precision);
int double_to_e_string(char **string_pointer, double number);
int get_number_length(long long number, int base);
int string_to_string(char **string_pointer, char *string_input, int flags,
                     int width, int precision);
int string_to_p(char **string_pointer, void *string_input, int flags, int width,
                int precision);
int char_to_string(char **string_pointer, char char_input, int flags,
                   int width);

int s21_sprintf(char *str, const char *format, ...) {
  setlocale(LC_ALL, "en_US.UTF-8");
  int flags = 0, width = 0, precision = 0, length = 0;
  specificators specificator;
  int status = SUCCEED;
  va_list argument_list;
  va_start(argument_list, format);
  long long number;
  long double double_number;
  char symbol;
  char *string_for_print;
  long long num_of_printed_char = 0;
  while (status == SUCCEED && *format) {
    if (*format != '%') {
      *str = *format++;
      str++;
      num_of_printed_char++;
    } else {
      format++;
      status = parse_specificator(&format, &flags, &width, &precision, &length,
                                  &specificator, argument_list);
      switch (specificator) {
        case C:
          if (length & L_LENGHT_FLAG) {
            int arg = 0;
            arg = (wchar_t)va_arg(argument_list, int);
            char buffer[10] = "";
            wctomb(buffer, arg);
            num_of_printed_char +=
                string_to_string(&str, buffer, flags, width, precision);
          } else {
            symbol = (char)va_arg(argument_list, int);
            num_of_printed_char += char_to_string(&str, symbol, flags, width);
          }
          break;
        case N:
          int *arg = S21_NULL;
          arg = va_arg(argument_list, int *);
          number = num_of_printed_char;
          *arg = number;
          break;
        case F:
          if (length & L_CAPS_LENGHT_FLAG) {
            double_number = va_arg(argument_list, long double);
          } else {
            double_number = va_arg(argument_list, double);
          }
          double_number = (length & L_CAPS_LENGHT_FLAG) ? double_number
                                                        : (double)double_number;
          num_of_printed_char +=
              double_to_string(&str, double_number, flags, width, precision);
          break;
        case S:
          if (length & L_LENGHT_FLAG) {
            void *arg = NULL;
            arg = (wchar_t *)va_arg(argument_list, wchar_t *);
            char buffer[10000] = "";
            wcstombs(buffer, arg, 10000);
            num_of_printed_char +=
                string_to_string(&str, buffer, flags, width, precision);
          } else {
            string_for_print = va_arg(argument_list, char *);
            num_of_printed_char += string_to_string(&str, string_for_print,
                                                    flags, width, precision);
          }
          break;
        case PERCENT:
          *str = '%';
          str++;
          num_of_printed_char++;
          break;
        case I:
          number = va_arg(argument_list, long);
          number = (length & H_LENGHT_FLAG) ? (short)number : number;
          number = (length & L_LENGHT_FLAG) ? number : (int)number;
          num_of_printed_char +=
              int_to_string(&str, number, flags, width, precision, 10);
          break;
        case U:
          if (flags & SPACE_FLAG) flags = flags - SPACE_FLAG;
          if (flags & PLUS_FLAG) flags = flags - PLUS_FLAG;
          number = va_arg(argument_list, long unsigned int);
          number =
              (length & H_LENGHT_FLAG) ? (short unsigned int)number : number;
          number = (length & L_LENGHT_FLAG) ? number : (unsigned int)number;
          num_of_printed_char +=
              int_to_string(&str, number, flags, width, precision, 10);
          break;
        case D:
          number = va_arg(argument_list, long);
          number = (length & H_LENGHT_FLAG) ? (short)number : number;
          number = (length & L_LENGHT_FLAG) ? number : (int)number;
          num_of_printed_char +=
              int_to_string(&str, number, flags, width, precision, 10);
          break;
        case X:
          number = va_arg(argument_list, long unsigned int);
          number = (length & H_LENGHT_FLAG) ? (short)number : number;
          number = (length & L_LENGHT_FLAG) ? number : (int)number;
          num_of_printed_char +=
              int_to_string(&str, number, flags, width, precision, 16);
          break;
        case x:
          flags |= NO_CAPS_FLAG;
          number = va_arg(argument_list, long unsigned int);
          number = (length & H_LENGHT_FLAG) ? (short)number : number;
          number = (length & L_LENGHT_FLAG) ? number : (int)number;
          num_of_printed_char +=
              int_to_string(&str, number, flags, width, precision, 16);
          break;
        case O:
          number = va_arg(argument_list, long);
          number = (length & H_LENGHT_FLAG) ? (short)number : number;
          number = (length & L_LENGHT_FLAG) ? number : (int)number;
          num_of_printed_char +=
              int_to_string(&str, number, flags, width, precision, 8);
          break;
        case P:
          flags |= NO_CAPS_FLAG;
          flags |= SHARP_FLAG;
          number = va_arg(argument_list, long unsigned int);
          num_of_printed_char +=
              int_to_string(&str, number, flags, width, precision, 16);
          break;
        case e:
          double_number = va_arg(argument_list, double);
          num_of_printed_char += double_to_e_string(&str, double_number);
          break;
        default:
          break;
      }
    }
  }
  *str = 0;
  va_end(argument_list);
  return num_of_printed_char;
}

int parse_specificator(const char **format_pointer, int *flags, int *width,
                       int *precision, int *length, specificators *specificator,
                       va_list arg_list) {
  int status = SUCCEED;
  status = get_flags(format_pointer, flags);
  if (status == SUCCEED) status = get_width(format_pointer, width, arg_list);
  if (status == SUCCEED)
    status = get_precision(format_pointer, precision, arg_list);
  if (status == SUCCEED) status = get_length(format_pointer, length);
  if (status == SUCCEED)
    status = get_specificator(format_pointer, specificator);
  return status;
}

int get_flags(const char **format_pointer, int *flags) {
  const char *format = *format_pointer;
  int status = SUCCEED;
  int _flags = 0;

  while (status == SUCCEED && is_flag(*format)) {
    if (*format == '+') {
      if (_flags & PLUS_FLAG) {
        status = ERROR;
      } else {
        _flags |= PLUS_FLAG;
      }
      format++;
    } else if (*format == '-') {
      if (_flags & MINUS_FLAG) {
        status = ERROR;
      } else {
        _flags |= MINUS_FLAG;
      }
      format++;
    } else if (*format == ' ') {
      if (_flags & SPACE_FLAG) {
        status = ERROR;
      } else {
        _flags |= SPACE_FLAG;
      }
      format++;
    } else if (*format == '#') {
      if (_flags & SHARP_FLAG) {
        status = ERROR;
      } else {
        _flags |= SHARP_FLAG;
      }
      format++;
    } else if (*format == '0') {
      if (_flags & ZERO_FLAG) {
        status = ERROR;
      } else {
        _flags |= ZERO_FLAG;
      }
      format++;
    } else {
      status = ERROR;
    }
  }
  *flags = status == SUCCEED ? _flags : 0;
  *format_pointer = format;
  return status;
}

int get_width(const char **format_pointer, int *width, va_list arg_list) {
  const char *format = *format_pointer;
  int status = SUCCEED;
  unsigned int _width = 0;

  while (status == SUCCEED && (is_digit(*format) || *format == '*')) {
    if (*format == '*') {
      _width = va_arg(arg_list, int);
      format++;
    } else {
      _width *= 10;
      _width += *format - '0';
      if (_width > INT_MAX) {
        status = ERROR;
      } else {
        format++;
      }
    }
  }
  if (status == SUCCEED) {
    *format_pointer = format;
    *width = (int)_width;
  }
  return status;
}

int get_precision(const char **format_pointer, int *precision,
                  va_list arg_list) {
  const char *format = *format_pointer;
  int status = SUCCEED;
  unsigned int _precision = 0;

  if (*format == '.') {
    format++;
    while (status == SUCCEED && (is_digit(*format) || *format == '*')) {
      if (*format == '*') {
        _precision = va_arg(arg_list, int);
      } else {
        _precision *= 10;
        _precision += *format - '0';
      }
      format++;
      if (_precision + *format - '0' > INT_MAX) {
        status = ERROR;
      }
    }
    if (status == SUCCEED) {
      *format_pointer = format;
      *precision = (int)_precision;
    }
  } else {
    *precision = -1;
  }
  return status;
}

int get_length(const char **format_pointer, int *length) {
  const char *format = *format_pointer;
  int _length = 0;
  int status = SUCCEED;

  if (*format == 'h') {
    _length |= H_LENGHT_FLAG;
    format++;
  } else if (*format == 'l') {
    _length |= L_LENGHT_FLAG;
    format++;
  } else if (*format == 'L') {
    _length |= L_CAPS_LENGHT_FLAG;
    format++;
  }

  *length = status == SUCCEED ? _length : *length;
  *format_pointer = format;
  return status;
}

int get_specificator(const char **format_pointer, specificators *specificator) {
  char format = (*format_pointer)[0];
  specificators _specificator = 0;
  int status = SUCCEED;

  if (is_specificator(format)) {
    if (format == 'c') {
      _specificator = C;
    } else if (format == 'f') {
      _specificator = F;
    } else if (format == 's') {
      _specificator = S;
    } else if (format == '%') {
      _specificator = PERCENT;
    } else if (format == 'i') {
      _specificator = I;
    } else if (format == 'u') {
      _specificator = U;
    } else if (format == 'd') {
      _specificator = D;
    } else if (format == 'X') {
      _specificator = X;
    } else if (format == 'x') {
      _specificator = x;
    } else if (format == 'o') {
      _specificator = O;
    } else if (format == 'p') {
      _specificator = P;
    } else if (format == 'G') {
      _specificator = G;
    } else if (format == 'E') {
      _specificator = E;
    } else if (format == 'g') {
      _specificator = g;
    } else if (format == 'e') {
      _specificator = e;
    } else if (format == 'n') {
      _specificator = N;
    } else {
      status = ERROR;
    }
  } else {
    status = ERROR;
  }
  *specificator = status == SUCCEED ? _specificator : *specificator;
  *format_pointer += 1;
  return status;
}

int is_flag(char c) {
  return c == '+' || c == '-' || c == ' ' || c == '#' || c == '0';
}

int is_digit(char c) { return c >= '0' && c <= '9'; }

int is_specificator(char c) {
  return c == 'c' || c == 'd' || c == 'i' || c == 'f' || c == 's' || c == 'u' ||
         c == 'x' || c == 'X' || c == 'g' || c == 'G' || c == 'e' || c == 'E' ||
         c == 'o' || c == 'p' || c == '%' || c == 'n';
}

int int_to_string(char **string_pointer, long long int number, int flags,
                  int width, int precision, int base) {
  int old_precision = precision;
  precision = precision == -1 ? 0
                              : precision + (number < 0 || flags & PLUS_FLAG ||
                                             flags & SPACE_FLAG);
  int length = get_number_length(number, base) +
               (number < 0 || flags & PLUS_FLAG || flags & SPACE_FLAG);
  width = (length >= width) ? length : width;
  width = (width > precision) ? width : precision;
  char *string = *string_pointer;
  if (flags & ZERO_FLAG && !(flags & MINUS_FLAG)) {
    s21_memset(string, '0', width);
  } else {
    s21_memset(string, ' ', width);
  }

  long long int abs_number = number >= 0 ? number : -number;
  char *end_of_number =
      (flags & MINUS_FLAG)
          ? (length > precision) ? (string + length) : (string + precision)
          : (string + width);
  end_of_number--;
  char *end_of_symbol = (length > precision) ? (end_of_number + 1 - length)
                                             : (end_of_number + 1 - precision);
  char *precision_end = end_of_number;
  for (; precision; precision--, precision_end--) {
    *precision_end = '0';
  }

  if (flags & PLUS_FLAG) {
    *end_of_symbol = number >= 0 ? '+' : '-';
  } else if (flags & SPACE_FLAG) {
    *end_of_symbol = number >= 0 ? ' ' : '-';
  } else if (number < 0) {
    *end_of_symbol = '-';
  }
  if (!abs_number) {
    *end_of_number = '0';
  } else if (base == 8) {
    for (; number > 0; number /= base, end_of_number--) {
      *end_of_number = number % base + '0';
    }
  } else {
    for (; abs_number > 0; abs_number /= base, end_of_number--) {
      if (base == 16 && (flags & NO_CAPS_FLAG)) {
        *end_of_number = abs_number % base + '0';
        if (*end_of_number == ':' || *end_of_number == '>' ||
            *end_of_number == '=' || *end_of_number == ';' ||
            *end_of_number == '<' || *end_of_number == '?') {
          *end_of_number = abs_number % base + 87;
        } else {
          *end_of_number = abs_number % base + '0';
        }
      } else if (base == 16 && !(flags & NO_CAPS_FLAG)) {
        *end_of_number = abs_number % base + '0';
        if (*end_of_number == ':' || *end_of_number == '>' ||
            *end_of_number == '=' || *end_of_number == ';' ||
            *end_of_number == '<' || *end_of_number == '?') {
          *end_of_number = abs_number % base + '7';
        } else {
          *end_of_number = abs_number % base + '0';
        }
      } else {
        *end_of_number = abs_number % base + '0';
      }
    }
  }

  width = (number == 0 && precision == 0 && (flags & SPACE_FLAG) == 0 &&
           old_precision == 0)
              ? 0
              : width;
  if (flags & SHARP_FLAG && base == 16 && flags & NO_CAPS_FLAG) {
    int l = width + 2;
    char tmp[width + 2];
    for (int i = 0; i < l; i++) {
      if (i == 0) tmp[i] = '0';
      if (i == 1) tmp[i] = 'x';
      if (i != 0 && i != 1) tmp[i] = string[i - 2];
    }
    for (int i = 0; i < l; i++) {
      string[i] = tmp[i];
    }
    *string_pointer += width + 2;
  } else if (flags & SHARP_FLAG && base == 16 && !(flags & NO_CAPS_FLAG)) {
    int l = width + 2;
    char tmp[width + 2];
    for (int i = 0; i < l; i++) {
      if (i == 0) tmp[i] = '0';
      if (i == 1) tmp[i] = 'X';
      if (i != 0 && i != 1) tmp[i] = string[i - 2];
    }
    for (int i = 0; i < l; i++) {
      string[i] = tmp[i];
    }
    *string_pointer += width + 2;
  } else if (flags & SHARP_FLAG && base == 8) {
    int l = width + 1;
    char tmp[width + 1];
    for (int i = 0; i < l; i++) {
      if (i == 0) tmp[i] = '0';
      if (i != 0) tmp[i] = string[i - 1];
    }
    for (int i = 0; i < l; i++) {
      string[i] = tmp[i];
    }
    *string_pointer += width + 1;
  } else {
    *string_pointer += width;
  }
  return width;
}

int double_to_string(char **string_pointer, long double number, int flags,
                     int width, int precision) {
  char *string = *string_pointer;
  int temp = 0;
  precision = (precision == -1) ? 6 : precision;
  int i = precision;  // i - Счетчик оставшихся знаков после запятой
  int j = 0;          // j - Позиция в выходной строке
  long double abs_number = fabsl(number);
  s21_size_t int_length = 1;  // Длина целой части
  if (abs_number >= 1) {
    int_length = get_number_length(abs_number, 10);
  }
  s21_size_t length = int_length + precision +
                      (number < 0 || flags & PLUS_FLAG || flags & SPACE_FLAG) +
                      (precision != 0);
  width -= length;
  abs_number = abs_number *
               pow(10, precision);  // Округление числа до ближайшего четного
  long double intpart = 0;
  long double fractpart = modfl((round(abs_number * 10) / 10), &intpart);
  if (fractpart != 0.5) {
    abs_number = roundl(abs_number);
  } else if ((int)abs_number % 2 == 0) {
    abs_number = floorl(abs_number);
  } else {
    abs_number = roundl(abs_number);
  }
  i += int_length;
  while (width > 0 && (flags & MINUS_FLAG) == 0) {  // Формирование строки
    if (flags & ZERO_FLAG) {
      string[j] = '0';
    } else {
      string[j] = ' ';
    }
    j++;
    width--;
  }
  if (flags & PLUS_FLAG) {  // Обработка флагов для записи первого символа
    string[j] = number >= 0 ? '+' : '-';
    j++;
  } else if (flags & SPACE_FLAG) {
    string[j] = number >= 0 ? ' ' : '-';
    j++;
  } else if (number < 0) {
    string[j] = '-';
    j++;
  }
  while (i > 0) {  // Запись числа
    temp = fmodl(abs_number / (powl(10, i - 1)), 10);  // Выделение цифры
    string[j] = temp + '0';  // Запись цифры
    i--;
    j++;
    if (i == precision && i != 0) {
      string[j] = '.';
      j++;
    }
  }
  while (width > 0) {  // Запись конечных пробелов, если флаг минус
    string[j] = ' ';
    j++;
    width--;
  }
  string[j] = '\0';
  *string_pointer += j;
  return j;
}

int double_to_e_string(char **string_pointer, double number) {
  char *string = *string_pointer;
  int temp = 0;
  int i = 0;  // i - Счетчик оставшихся знаков после запятой
  int j = 0;  // j - Позиция в выходной строке
  long double abs_number = fabs(number);
  s21_size_t int_length = 1;  // Длина целой части
  if (abs_number >= 1) {
    int_length = get_number_length(abs_number, 10);
  }
  // s21_size_t length = int_length +
  //                     (number < 0);// Округление числа до ближайшего четного
  long double intpart = 0;
  long double fractpart = modfl((round(abs_number * 10) / 10), &intpart);
  if (fractpart != 0.5) {
    abs_number = roundl(abs_number);
  } else if ((int)abs_number % 2 == 0) {
    abs_number = floorl(abs_number);
  } else {
    abs_number = roundl(abs_number);
  }
  i += int_length;

  while (i > 0) {  // Запись числа
    temp = fmodl(abs_number / (powl(10, i - 1)), 10);  // Выделение цифры
    string[j] = temp + '0';  // Запись цифры
    i--;
    j++;
    if (j == 1) {
      string[j] = '.';
      j++;
    }
    if (i == 0) {
      string[j + 1] = '0';
      string[j + 2] = '0';
      string[j + 3] = 'e';
      string[j + 4] = '0';
      string[j + 5] = (j - 1) + '0';
    }
  }

  string[j + 6] = '\0';
  *string_pointer += (j + 6);
  return j + 6;
}

int get_number_length(long long number, int base) {
  number = number < 0 ? -number : number;
  return (number >= 1) ? (int)(log(number) / log(base)) + 1 : 1;
}

int string_to_string(char **string_pointer, char *string_input, int flags,
                     int width, int precision) {
  char *string = *string_pointer;
  char null[7] = "(null)";
  string_input = (string_input) ? string_input : null;
  // Length of the formatted string
  int length = s21_strlen(string_input);
  // Shortening the string to the precision
  length = (precision <= length && precision >= 0) ? precision : length;
  // Adding extra spaces if width is greater than length
  width = (length >= width) ? length : width;
  s21_memset(string, ' ', width);
  if (!(flags & MINUS_FLAG)) {  // Left alignment
    string += width - length;
  }
  while (length) {
    *string = *string_input;
    string++;
    string_input++;
    length--;
  }

  *string_pointer += width;
  return width;
}

int char_to_string(char **string_pointer, char char_input, int flags,
                   int width) {
  char *string = *string_pointer;
  width = (1 >= width) ? 1 : width;
  s21_memset(string, ' ', width);
  if (!(flags & MINUS_FLAG)) {  // Left alignment
    string += width - 1;
  }
  *string = char_input;
  string++;
  *string_pointer += width;
  return width;
}