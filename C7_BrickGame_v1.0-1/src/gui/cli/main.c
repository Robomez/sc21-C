#include "cli.h"

void Init();
int Final();

int main(void) {
  Init();
  RenderGame();
  Final();
  return 0;
}

void Init() {
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
}

int Final() {
  refresh();
  curs_set(1);
  endwin();
  return 0;
}