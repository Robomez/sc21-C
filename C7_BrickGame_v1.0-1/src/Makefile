.PHONY: all, install, uninstall, clean, dvi, dist, test, gcov_report
# .SILENT: clean compile_gcov test

CC=gcc
CFLAGS-COMP= -c -Wall -Werror -Wextra -std=c11
CFLAGS-LINK= -Wall -Werror -Wextra -std=c11
LDFLAGS = -lncurses
FUN_DIR := functions
COVERAGE = --coverage

TETRIS_DIR=brick_game/tetris
TETRIS_OBJ_DIR=$(TETRIS_DIR)/obj
TETRIS_LIB_DIR=$(TETRIS_DIR)/lib
TETRIS_LIB = $(TETRIS_LIB_DIR)/s21_tetris.a
TETRIS_SRC := $(filter-out $(TETRIS_DIR)/*.test.c, $(wildcard $(TETRIS_DIR)/*.c))
TETRIS_OBJ=$(TETRIS_SRC:$(TETRIS_DIR)/%.c=$(TETRIS_OBJ_DIR)/%.c.o)
TETRIS_TESTS_DIR=$(TETRIS_DIR)/tests

GUI_CLI_DIR=gui/cli
GUI_CLI_OBJ_DIR=$(GUI_CLI_DIR)/obj
GUI_CLI_OUT_DIR=bin
GUI_BINARY=$(GUI_CLI_OUT_DIR)/tetris
GUI_CLI_SRC=$(wildcard $(GUI_CLI_DIR)/*.c)
GUI_CLI_OBJ=$(GUI_CLI_SRC:$(GUI_CLI_DIR)/%.c=$(GUI_CLI_OBJ_DIR)/%.c.o)

PACKAGE_CFG=`pkg-config --cflags --libs check`
REPORT_DIR=report_gcovr

TEST_BINARY=$(TETRIS_TESTS_DIR)/test.out
REPORT_BINARY = $(REPORT_DIR)/report.out

GCOV_OBJECTS := $(TETRIS_SRC:%=$(REPORT_DIR)/%.o)
REPORT_FILE = $(REPORT_DIR)/report.html
OPEN_REPORT = open $(REPORT_FILE) 2>/dev/null 1>/dev/null

DIST = brick_game_tetris.tar.gz

DOXYGEN_DIR = docs/html
DOXYGEN_FILE = $(DOXYGEN_DIR)/index.html
OPEN_DOXYGEN = open $(DOXYGEN_FILE) 2>/dev/null 1>/dev/null

UNAME_S := $(shell uname -s)
UNAME_O := $(shell uname -o)
ifeq ($(UNAME_S),Linux)
	GCOV_FLAGS := --gcov-exclude $(TETRIS_TESTS_DIR)
	LEAKS_CMD := CK_FORK=no valgrind --tool=memcheck --leak-check=full --track-origins=yes -s $(TEST_BINARY)
	GUI_LEAKS_CMD := CK_FORK=no valgrind --tool=memcheck --leak-check=full --track-origins=yes -s $(GUI_BINARY)
	INSTALL_CMD := apt -y 
	NCURSES_INSTALL := libncurses5-dev libncursesw5-dev
	LDFLAGS :=
endif
ifeq ($(UNAME_S),Darwin)
	GCOV_FLAGS := -e $(TETRIS_TESTS_DIR)
	LEAKS_CMD := CK_FORK=no leaks --atExit -- $(TEST_BINARY)
	GUI_LEAKS_CMD := CK_FORK=no leaks --atExit -- $(GUI_BINARY)
	INSTALL_CMD := brew
	NCURSES_INSTALL := ncurses
	LDFLAGS := -lncurses
endif
ifeq ($(UNAME_O), Linux)
	CFLAGS += -DALPINE
	INSTALL_CMD := apt -y
endif

##### TARGETS
# general
all: install

install: tetris.a gui
	@echo "Installed game to src/bin/tetris"

uninstall: 
	@rm -f ./bin/tetris
	@echo "Uninstalled game from src/bin/tetris"

run:
	./bin/tetris

rebuild: clean all

# back
tetris.a: $(TETRIS_OBJ)
	@mkdir -p $(TETRIS_LIB_DIR)
	@ar rc $(TETRIS_LIB) $(TETRIS_OBJ)
	@ranlib $(TETRIS_LIB)

$(TETRIS_OBJ_DIR)/%.c.o: $(TETRIS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS-COMP) $< -o $@

# front
gui: $(GUI_CLI_OBJ) $(TETRIS_LIB)
	@mkdir -p $(GUI_CLI_OUT_DIR)
	@echo $(GUI_CLI_OBJ_DIR)
	@$(CC) $(CFLAGS_LINK) -o $(GUI_BINARY) $(GUI_CLI_OBJ) $(TETRIS_LIB) -lncurses

$(GUI_CLI_OBJ_DIR)/%.c.o: $(GUI_CLI_DIR)/%.c
	@mkdir -p $(GUI_CLI_OBJ_DIR)
	$(CC) $(CFLAGS-COMP) $< -o $@

# dist
dist: clean
	tar -cvf $(DIST) ./

# test
test: clean compile_gcov $(TETRIS_SRC)
	@mkdir -p $(TETRIS_TESTS_DIR)
	@$(CC) $(CFLAGS-LINK) $(COVERAGE) $(TETRIS_TESTS_DIR)/*.c $(TETRIS_LIB) -o $(TEST_BINARY) $(PACKAGE_CFG) $(LDFLAGS)
	@$(TEST_BINARY)
	gcovr $(GCOV_FLAGS) -s --exclude $(TETRIS_TESTS_DIR) 
	@make clean_tests

# gcov
$(REPORT_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS-LINK) $(COVERAGE) -c $< -o $@

compile_gcov: tetris.a $(GCOV_OBJECTS)
	@ar rc $(TETRIS_LIB) $(GCOV_OBJECTS)
	@ranlib $(TETRIS_LIB)

gcov_report: clean compile_gcov $(TETRIS_SRC)
	mkdir -p $(REPORT_DIR)
	$(CC) $(CFLAGS-LINK) $(COVERAGE) $(TETRIS_TESTS_DIR)/*.c $(HEADERS) $(TETRIS_LIB) -o $(REPORT_BINARY) $(PACKAGE_CFG) $(LDFLAGS)
	$(REPORT_BINARY) 
	gcovr $(GCOV_FLAGS) -o $(REPORT_FILE) --html-details --exclude $(TETRIS_TESTS_DIR)
	make clean_tests
	@$(OPEN_REPORT)

# leaks
leaks: clean tetris.a $(TETRIS_SRC)
	$(CC) $(CFLAGS-LINK) $(COVERAGE) $(TETRIS_TESTS_DIR)/*.c $(TETRIS_LIB) -o $(TEST_BINARY) $(PACKAGE_CFG) $(LDFLAGS)
	$(LEAKS_CMD) || true
	
# clean
clean:
	@echo "Cleaning..."
	@make clean_tests
	@rm -rf $(REPORT_DIR)
	@rm -rf $(TETRIS_OBJ_DIR) $(TETRIS_LIB_DIR)
	@rm -rf $(GUI_CLI_OBJ_DIR) $(GUI_CLI_OUT_DIR)
	@rm -rf docs
	@rm -f $(DIST)
	@rm -f high_score.txt

clean_tests:
	@echo "Cleaning tests..."
	@rm -rf $(GCOV_DIR) 
	@find . -name "*.gcno" -type f -delete
	@find . -name "*.gcda" -type f -delete
	@find . -name "*.o" -type f -delete
	@find . -name "*.out" -type f -delete

# dvi
dvi:
	@doxygen Doxyfile
	@$(OPEN_DOXYGEN)

# misc
clang:
	@echo "Check source code style with clang-format ..."
	find . -name "*.c" -exec clang-format -n --style=Google {} \;
	find . -name "*.h" -exec clang-format -n --style=Google {} \;

clang-fix:
	@find . -name "*.c" -exec clang-format -i --style=Google {} \;
	@find . -name "*.h" -exec clang-format -i --style=Google {} \;

# libs install
dev_install:
	@echo "Installing packages and libs..."
	$(INSTALL_CMD) install check gcovr pkg-config cppcheck doxygen graphviz $(NCURSES_INSTALL)

dev_uninstall:
	@echo "Removing packages and libs..."
	$(INSTALL_CMD) remove check gcovr pkg-config cppcheck doxygen graphviz $(NCURSES_INSTALL)