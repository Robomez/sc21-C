CC=gcc
CL=clang
CFLAGS= -c -Wall -Werror -Wextra -std=c11
FLAGS= -Wall -Werror -Wextra -std=c11
# LDFLAGS = -lcheck -lsubunit -lm -pthread
FUN_DIR := functions
TEST_DIR := tests

FUN_FILES := $(shell find $(FUN_DIR) -type f -name "*.c") # список си файлов в function
TEST_FILES := $(shell find $(TEST_DIR) -type f -name "*.c") # список си файлов в test 

FUN_OBJ := $(FUN_FILES:.c=.o) # список обектных библиотечных файлов
TEST_OBJ := $(TEST_FILES:.c=.o) # список обектных тестовых файлов

$(FUN_DIR)/%.o: $(FUN_DIR)/%.c # обектные файлы для библиотеки
	@$(CC) $(CFLAGS) $< -o $@

OS=$(shell uname -s)

ifeq ($(OS),Linux)
	test_libs=-lcheck -lm -lsubunit
	open=xdg-open
	comp=$(CC)
	GFLAGS= -fprofile-arcs -ftest-coverage
else
	test_libs=-lcheck
	open=open
	comp=$(CL)
	GFLAGS= -fprofile-arcs -ftest-coverage -I/opt/homebrew/Cellar/check/0.15.2/include -L/opt/homebrew/Cellar/check/0.15.2/lib
endif

all: s21_decimal.a test gcov_report
# all: s21_decimal.a test 
# all: main

s21_decimal.a: $(FUN_OBJ)
	@ar rcs s21_decimal.a $(FUN_OBJ)
	@rm -rf functions/*.o 
	@echo "lib build done"

test:
	@$(CC) $(FLAGS) $(GFLAGS) *.c $(FUN_FILES) $(TEST_FILES) -o Test $(test_libs)
	@-./Test #чтобы скрипт при завале тесте не вставал, а делал дальше gcov_report	
# ./Test

gcov_report:
	@lcov -t "testones" -o test.info -c -d . > /dev/null 2>&1 --exclude '*/math.h'
	@genhtml -o report test.info > /dev/null 2>&1
	@open 'report/index.html'
	@echo "gcov_report ready"

tsanitize: s21_decimal.a
	$(comp) $(FLAGS) $(GFLAGS) -fsanitize=address -g *.c $(FUN_FILES) $(TEST_FILES) -o Test $(test_libs)
	./Test

main:
	@$(CC) $(FLAGS) main.c \
	functions/arithmetics/s21_add.c functions/arithmetics/s21_sub.c \
	functions/arithmetics/s21_mul.c functions/arithmetics/s21_div.c \
	functions/compare/s21_is_greater.c functions/compare/s21_is_equal.c \
	functions/compare/s21_is_greater_or_equal.c functions/compare/s21_is_not_equal.c \
	functions/compare/s21_is_less_or_equal.c functions/compare/s21_is_less.c \
	functions/convertors/s21_from_int_to_decimal.c functions/convertors/s21_from_decimal_to_int.c \
	functions/convertors/s21_from_float_to_decimal.c functions/convertors/s21_from_decimal_to_float.c \
	functions/others/s21_negate.c \
	functions/helpers/arith_help/s21_numbers_add.c functions/helpers/arith_help/s21_to_zero.c \
	functions/helpers/arith_help/s21_big_mantissa_add.c functions/helpers/arith_help/s21_big_mantissa_sub.c \
	functions/helpers/arith_help/s21_big_mul10.c functions/helpers/arith_help/s21_big_div10.c \
	functions/helpers/arith_help/s21_is_zero.c functions/helpers/arith_help/s21_decimal_div10.c \
	functions/helpers/arith_help/s21_big_mul.c functions/helpers/arith_help/s21_big_div.c \
	functions/helpers/comp_help/s21_big_is_mantissa_greater.c \
	functions/helpers/get,set/s21_decimal_sign_get.c functions/helpers/get,set/s21_decimal_sign_set.c	functions/helpers/get,set/s21_bit_set.c \
	functions/helpers/get,set/s21_bit_reverse.c functions/helpers/get,set/s21_bit_get.c \
	functions/helpers/get,set/s21_decimal_precision_set.c functions/helpers/get,set/s21_decimal_precision_get.c \
	functions/helpers/get,set/s21_big_precision_set.c functions/helpers/get,set/s21_big_precision_get.c \
	functions/helpers/get,set/s21_big_sign_get.c functions/helpers/get,set/s21_big_sign_set.c \
	functions/helpers/print/s21_number_print_binary.c functions/helpers/print/s21_number_print_denary.c functions/helpers/print/s21_number_print_hex.c \
	functions/helpers/print/s21_decimal_print_binary.c functions/helpers/print/s21_decimal_print_denary.c functions/helpers/print/s21_decimal_print_hex.c \
	functions/helpers/print/s21_big_print_binary.c functions/helpers/print/s21_big_print_denary.c functions/helpers/print/s21_big_print_hex.c \
	functions/helpers/print/s21_big_print_hex_oneline.c functions/helpers/print/s21_decimal_print_hex_oneline.c \
	functions/helpers/shift/s21_number_shift_left.c functions/helpers/shift/s21_number_shift_right.c \
	functions/helpers/shift/s21_decimal_shift_left.c functions/helpers/shift/s21_decimal_shift_right.c \
	functions/helpers/shift/s21_big_shift_left.c functions/helpers/shift/s21_big_shift_right.c \
	functions/helpers/s21_decimal_to_big.c functions/helpers/s21_decimal_is_ok.c functions/helpers/s21_big_normalize.c \
	functions/helpers/s21_big_to_decimal.c functions/helpers/s21_decimal_remove_zeros.c \
	-lm -o main
	@echo "make main done"
	./main

msanitize: s21_decimal.a
	$(comp) $(FLAGS) $(GFLAGS) -fsanitize=address -g main.c functions/s21_insert.c -o main $(test_libs)

clean:
	@rm -rf $(FUN_OBJ) $(TEST_OBJ) *.a *.gcno *.gcda *.dSYM coverage.info coverage_report Test \
	report/ test.info main
	@echo "make clean done"

clang:
	clang-format --style=Google -i **/*.c

rebuild: clean all
