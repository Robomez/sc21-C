#include "cli.h"

void RenderGame() {
  userInput(Start, false);
  updateCurrentState();
  clear();

  GameWindows windows = {0};
  InitWindows(&windows);

  if (RenderStartScreen(windows.game_over)) {
    DeleteWindows(&windows);
    standend();
    return;
  }

  timeout(0);
  keypad(windows.game, TRUE);

  int stop = 0;
  while (!stop) {
    GameInfo_t currentState = updateCurrentState();
    if (currentState.field == NULL || currentState.next == NULL) {
      RenderGameOver(windows.game_over, currentState.score,
                     currentState.high_score);
      timeout(-1);
      while (getch() != ESC && getch() != '\n') {
      }
      stop = 1;
      break;
    } else {
      RenderPause(windows.pause, currentState.pause);
      RenderField(windows.inner_field, currentState.field);
      RenderNextFigure(windows.next, currentState.next);
      RenderScore(windows.score, currentState.score);
      RenderHighScore(windows.high_score, currentState.high_score);
      RenderLevel(windows.level, currentState.level);
      refresh();
    }

    stop = UserActionHandler();
  }

  timeout(-1);

  DeleteWindows(&windows);
  standend();
}