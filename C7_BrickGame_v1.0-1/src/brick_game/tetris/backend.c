/**
 * @file backend.c
 * @brief Содержит основную логику игры Тетрис, включая управление состоянием
 * игры, обработку пользовательского ввода и обновление игрового поля.
 */

#include "backend_internal.h"

/**
 * @brief Возвращает указатель на статическую переменную,
 * которая хранит текущее состояние игры.
 * @return Указатель на game_state_t.
 */
game_state_t* GetGameState() {
  static game_state_t state = Starting;
  return &state;
}

/**
 * @brief Возвращает указатель на статическую структуру,
 * которая хранит всю информацию об игре (поле, счет, уровень и т.д.).
 * @return Указатель на GameInfo_t.
 */
GameInfo_t* GetGameInfo() {
  static GameInfo_t game_info = {0};
  return &game_info;
}

/**
 * @brief Возвращает указатель на статическую структуру,
 * которая хранит информацию о следующей фигуре.
 * @return Указатель на figure_t.
 */
figure_t* GetNextFigure() {
  static figure_t next_figure = {0};
  return &next_figure;
}

/**
 * @brief Возвращает указатель на статическую структуру,
 * которая хранит информацию о текущей активной фигуре.
 * @return Указатель на figure_t.
 */
figure_t* GetCurrentFigure() {
  static figure_t current_figure = {0};
  return &current_figure;
}

/**
 * @brief Обрабатывает действия пользователя и обновляет состояние игры.
 * @param action Действие пользователя (Start, Left, Right и т.д.).
 * @param hold Логическое значение, указывающее, удерживается ли кнопка.
 */
void userInput(UserAction_t action, bool hold) {
  game_state_t* game_state = GetGameState();
  if (*game_state == Paused && action != Pause && action != Terminate &&
      action != Start) {
    return;
  }

  switch (action) {
    case Start:
      *game_state = Starting;
      break;
    case Terminate:
      *game_state = GameOver;
      break;
    case Pause:
      *game_state = *game_state == Paused ? Continued : Paused;
      break;
    case Left:
      *game_state = MovingLeft;
      break;
    case Right:
      *game_state = MovingRight;
      break;
    case Up:
      break;
    case Down:
      *game_state = hold ? Dropping : MovingDown;
      break;
    case Action:
      *game_state = Rotating;
      break;
  }
}

/**
 * @brief Главная функция обновления состояния игры.
 * Она определяет текущее состояние и вызывает соответствующий обработчик.
 * @return Текущая информация об игре GameInfo_t.
 */
GameInfo_t updateCurrentState() {
  static unsigned long long previous_time = 0, current_time = 0;
  static unsigned long long delta_time = 0;

  GameInfo_t* game_info = GetGameInfo();
  game_state_t* game_state = GetGameState();

  figure_t* current_figure = GetCurrentFigure();
  figure_t* next_figure = GetNextFigure();

  handler_info_t info = {0};
  info.game_info = game_info;
  info.current_figure = current_figure;
  info.next_figure = next_figure;
  info.game_state = game_state;
  info.previous_time = &previous_time;
  info.current_time = &current_time;

  if (*game_state == Starting) {
    HandleStartingState(&info);
  } else if (*game_state == Spawning) {
    HandleSpawningState(&info);
  } else if (*game_state == MovingLeft) {
    MoveHorizontal(DirectionLeft, game_info, current_figure);
    *game_state = Falling;
  } else if (*game_state == MovingRight) {
    MoveHorizontal(DirectionRight, game_info, current_figure);
    *game_state = Falling;
  } else if (*game_state == MovingDown) {
    HandleMovingDownState(&info);
  } else if (*game_state == Dropping) {
    HandleDroppingState(&info);
  } else if (*game_state == Rotating) {
    HandleMovingRotateState(&info);
  } else if (*game_state == Falling) {
    HandleFallingState(&info);
  } else if (*game_state == Attaching) {
    HandleAttachingState(&info);
  } else if (*game_state == Paused) {
    game_info->pause = 1;
    delta_time = GetTime() - previous_time;
  } else if (*game_state == Continued) {
    HandleContinuedtate(&info);
    previous_time = GetTime() - delta_time;
  } else if (*game_state == GameOver) {
    StopGame(game_info, current_figure, next_figure);
  }

  return *game_info;
}

/**
 * @brief Обрабатывает состояние Starting (начало игры).
 * Инициализирует игру и переводит состояние в Spawning.
 * @param info Указатель на структуру с информацией для обработчика.
 */
void HandleStartingState(handler_info_t* info) {
  StartGame(info->game_info, info->current_figure, info->next_figure);
  GenerateNextFigure(info->next_figure);
  *(info->previous_time) = 0;
  *(info->current_time) = 0;
  *(info->game_state) = Spawning;
}

/**
 * @brief Обрабатывает состояние Spawning (появление новой фигуры).
 * Создает новую фигуру и переводит состояние в Falling или GameOver.
 * @param info Указатель на структуру с информацией для обработчика.
 */
void HandleSpawningState(handler_info_t* info) {
  int couldNotBeSpawned =
      SpawnFigure(info->game_info, info->current_figure, info->next_figure);
  *(info->game_state) = couldNotBeSpawned ? GameOver : Falling;
  *(info->previous_time) = GetTime();
}

/**
 * @brief Обрабатывает состояние Falling (падение фигуры).
 * Проверяет, прошло ли достаточно времени для следующего шага падения.
 * @param info Указатель на структуру с информацией для обработчика.
 */
void HandleFallingState(handler_info_t* info) {
  *(info->current_time) = GetTime();
  if ((int)(*(info->current_time) - *(info->previous_time)) >=
      info->game_info->speed) {
    *(info->game_state) = MovingDown;
    *(info->previous_time) = GetTime();
  }
}

/**
 * @brief Обрабатывает состояние MovingDown (движение фигуры вниз).
 * Передвигает фигуру на одну клетку вниз.
 * @param info Указатель на структуру с информацией для обработчика.
 */
void HandleMovingDownState(handler_info_t* info) {
  *(info->game_state) = Falling;
  if (MoveDown(info->game_info, info->current_figure) != 0) {
    *(info->game_state) = Attaching;
  }
}

/**
 * @brief Обрабатывает состояние Dropping (быстрое падение фигуры).
 * Передвигает фигуру до самого низа поля.
 * @param info Указатель на структуру с информацией для обработчика.
 */
void HandleDroppingState(handler_info_t* info) {
  Drop(info->game_info, info->current_figure);
  *(info->game_state) = Attaching;
}

/**
 * @brief Обрабатывает состояние Attaching (прикрепление фигуры).
 * Обновляет игровое поле и переводит состояние в Spawning.
 * @param info Указатель на структуру с информацией для обработчика.
 */
void HandleAttachingState(handler_info_t* info) {
  UpdateGameInfo(info->game_info);
  *(info->game_state) = Spawning;
}

/**
 * @brief Обрабатывает состояние Continued (продолжение игры).
 * Снимает игру с паузы и корректирует время.
 * @param info Указатель на структуру с информацией для обработчика.
 */
void HandleContinuedtate(handler_info_t* info) {
  info->game_info->pause = 0;
  *(info->game_state) = Falling;
}

/**
 * @brief Обрабатывает состояние MovingRotate (вращение фигуры).
 * Вращает текущую фигуру.
 * @param info Указатель на структуру с информацией для обработчика.
 */
void HandleMovingRotateState(handler_info_t* info) {
  RotateInField(info->game_info, info->current_figure);
  *(info->game_state) = Falling;
}