CC = gcc -std=c11
FLAGS = -Wall -Werror -Wextra

all: s21_cat

s21_cat: s21_cat.c
	$(CC) $(FLAGS) s21_cat.c -o s21_cat

sanitized: s21_cat.c
	$(CC) $(FLAGS) -fsanitize=address -g s21_cat.c -o sanitized

test:
	bash test.sh

clean:
	rm -rf *.o *.a s21_cat sanitized

clang:
	clang-format -i *.c *.h

rebuild: clean all