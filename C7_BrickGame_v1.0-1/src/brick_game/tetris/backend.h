#ifndef BACKEND_H_
#define BACKEND_H_

#include <stdbool.h>
#include <stdio.h>

/**
 * @file backend.h
 * @brief Заголовочный файл для бэкенда игры "Тетрис".
 *
 * Содержит объявления структур и функций, необходимых для управления состоянием
 * игры, логикой фигур и игровым полем.
 */

/**
 * @brief Перечисление действий пользователя.
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @struct GameInfo_t
 * @brief Структура, хранящая всю информацию о текущем состоянии игры.
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief Обрабатывает пользовательский ввод.
 * @param action Действие пользователя.
 * @param hold Логическое значение, указывающее, удерживается ли кнопка.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Обновляет текущее состояние игры.
 * @return Структура GameInfo_t с обновленными данными.
 */
GameInfo_t updateCurrentState();

#endif