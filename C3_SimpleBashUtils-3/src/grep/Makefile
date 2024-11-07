CC = gcc 
FLAGS = -Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep: s21_grep.c
	$(CC) $(FLAGS) s21_grep.c -o s21_grep

sanitized: s21_grep.c
	$(CC) $(FLAGS) -fsanitize=address -g s21_grep.c -o sanitized

test:
	bash test.sh

clean:
	rm -rf *.o *.a s21_grep sanitized

clang:
	clang-format -i *.c *.h

rebuild: clean all
