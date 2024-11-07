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

all: s21_matrix.a test gcov_report
# all: s21_matrix.a test 

s21_matrix.a: $(FUN_OBJ)
	@ar rcs s21_matrix.a $(FUN_OBJ)
	@rm -rf functions/*.o 
	@echo "lib build done"

test:
	@$(CC) $(FLAGS) $(GFLAGS) *.c $(FUN_FILES) $(TEST_FILES) -o Test $(test_libs)
	@-./Test #чтобы скрипт при завале теста не вставал, а делал дальше gcov_report	
# ./Test

gcov_report:
	@lcov -t "testones" -o test.info -c -d . > /dev/null 2>&1 --exclude '*/s21_print_matrix.c'
	@genhtml -o report test.info > /dev/null 2>&1
	@open 'report/index.html'
	@echo "gcov_report ready"

tsanitize: s21_matrix.a
	$(comp) $(FLAGS) $(GFLAGS) -fsanitize=address -g *.c $(FUN_FILES) $(TEST_FILES) -o Test $(test_libs)
	./Test

main:
	@$(CC) $(FLAGS) main.c \
	functions/s21_create_matrix.c functions/s21_remove_matrix.c functions/s21_eq_matrix.c \
	functions/s21_sum_matrix.c functions/s21_sub_matrix.c functions/s21_mult_number.c \
	functions/s21_mult_matrix.c functions/s21_transpose.c functions/s21_calc_complements.c \
	functions/s21_determinant.c functions/s21_inverse_matrix.c \
	helpers/s21_print_matrix.c helpers/s21_matrix_ok.c helpers/s21_matrices_same_size.c \
	helpers/s21_make_minor.c helpers/s21_calc_determ.c helpers/s21_init_matrix.c \
	-lm -o main
	@echo "make main done"
	./main

msanitize: s21_matrix.a
	$(comp) $(FLAGS) $(GFLAGS) -fsanitize=address -g main.c functions/s21_create_matrix.c -o main $(test_libs)

clean:
	@rm -rf $(FUN_OBJ) $(TEST_OBJ) *.a *.gcno *.gcda *.dSYM coverage.info coverage_report Test \
	report/ test.info main
	@echo "make clean done"

clang:
	clang-format --style=Google -i **/*.c

rebuild: clean all
