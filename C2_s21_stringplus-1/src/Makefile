CC=gcc
CL=clang
CFLAGS= -c -Wall -Werror -Wextra -std=c11
FLAGS= -Wall -Werror -Wextra -std=c11
GFLAGS= -fprofile-arcs -ftest-coverage
LDFLAGS = -lcheck -lsubunit -lm -pthread
FUN_DIR := functions
TEST_DIR := tests

FUN_FILES :=$(wildcard $(FUN_DIR)/*.c) # список си файлов в function
TEST_FILES :=$(wildcard $(TEST_DIR)/*.c) # список си файлов в test 

FUN_OBJ := $(patsubst $(FUN_DIR)/%.c,$(FUN_DIR)/%.o,$(FUN_FILES)) # список обектных библиотечных файлов
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c,$(TEST_DIR)/%.o,$(TEST_FILES)) # список обектных тестовых файлов

$(FUN_DIR)/%.o: $(FUN_DIR)/%.c # обектные файлы для библиотеки
	$(CC) $(CFLAGS) $< -o $@

OS=$(shell uname -s)

ifeq ($(OS),Linux)
	test_libs=-lcheck -lm -lsubunit
	open=xdg-open
	comp=$(CC)
else
	test_libs=-lcheck
	open=open
	comp=$(CL)
endif

all: s21_string.a test gcov_report

test:
	$(CC) $(FLAGS) $(GFLAGS) *.c $(FUN_FILES) $(TEST_FILES) -o Test $(test_libs)
	./Test

tsanitize: s21_string.a
	$(comp) $(FLAGS) $(GFLAGS) -fsanitize=address -g *.c $(FUN_FILES) $(TEST_FILES) -o Test $(test_libs)
	./Test

main:
	$(CC) $(FLAGS) main.c functions/s21_sprintf.c functions/s21_memset.c functions/s21_strlen.c \
	-lm -o main

msanitize: s21_string.a
	$(comp) $(FLAGS) $(GFLAGS) -fsanitize=address -g main.c functions/s21_insert.c -o main $(test_libs)

gcov_report:
	lcov -t "testones" -o test.info -c -d .
	genhtml -o report test.info
	open 'report/index.html'

s21_string.a: $(FUN_OBJ)
	ar rcs s21_string.a $(FUN_OBJ)
	rm -rf functions/*.o 

clean:
	rm -rf *.o */*.o *.a *.gcno *.gcda *.dSYM coverage.info coverage_report Test \
	report/ test.info main

clang:
	clang-format -i **/*.c **/*.h 

rebuild: clean all
