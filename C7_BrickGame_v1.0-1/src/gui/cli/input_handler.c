#include "cli.h"

int UserActionHandler() {
  int fBreak = 0;
  int key = getch();
  switch (key) {
    case KEY_LEFT:
      userInput(Left, false);
      break;
    case KEY_RIGHT:
      userInput(Right, false);
      break;
    case KEY_UP:
      break;
    case KEY_DOWN:
      userInput(Down, true);
      // userInput(Down, false);
      break;
    case 'p':
      userInput(Pause, false);
      break;
    case ' ':
      userInput(Action, false);
      break;
    case ESC:
      userInput(Terminate, false);
      fBreak = 1;
      break;
    default:
      break;
  }
  return fBreak;
}