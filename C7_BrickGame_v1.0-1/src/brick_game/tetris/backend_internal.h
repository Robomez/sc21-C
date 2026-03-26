#ifndef S21_BACKEND_INTERNAL_H_
#define S21_BACKEND_INTERNAL_H_

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "backend.h"

/**
 * @file backend_internal.h
 * @brief Заголовочный файл с внутренними структурами и функциями бэкенда.
 *
 * Содержит внутренние структуры, типы данных и объявления вспомогательных
 * функций, которые используются только внутри модуля бэкенда.
 */

// --- Константы для игры ---
#define MAX_LEVEL 10     ///< Максимальный уровень игры.
#define SPEED_BASE 1300  ///< Базовая скорость падения.
#define SPEED_STEP 80    ///< Шаг увеличения скорости.

#define FIELD_HEIGHT 20  ///< Высота игрового поля.
#define FIELD_WIDTH 10   ///< Ширина игрового поля.

#define LEVEL_SCORE \
  600  ///< Количество очков для перехода на следующий уровень.
#define POINTS_1_LINE 100    ///< Очки за одну линию.
#define POINTS_2_LINES 300   ///< Очки за две линии.
#define POINTS_3_LINES 700   ///< Очки за три линии.
#define POINTS_4_LINES 1500  ///< Очки за четыре линии.
#define HIGH_SCORE_FILE "high_score.txt"  ///< Имя файла для сохранения рекорда.

#define FIGURE_COUNT 7  ///< Количество типов фигур.

#define FIELD_SIGN_FIGURE 9  ///< Знак для отображения фигуры на поле.
#define FIELD_SIGN_TERRAIN 1  ///< Знак для отображения прикрепленной фигуры.
#define FIELD_SIGN_EMPTY 0  ///< Знак для отображения пустоты.

#define NEXT_FIGURE_ROWS 4  ///< Количество строк для матрицы следующей фигуры.
#define NEXT_FIGURE_COLS \
  4  ///< Количество столбцов для матрицы следующей фигуры.

// --- Типы фигур ---
#define figureI 0
#define figureJ 1
#define figureL 2
#define figureO 3
#define figureS 4
#define figureT 5
#define figureZ 6

#define RUNTIME_ERROR -1  ///< Код ошибки выполнения.

/**
 * @struct figure_t
 * @brief Структура, описывающая текущую или следующую фигуру.
 */
typedef struct {
  int **matrix;  ///< Матрица фигуры.
  int rows;  ///< Количество строк в матрице фигуры.
  int cols;  ///< Количество столбцов в матрице фигуры.
  int ul_row;  ///< Строка верхнего левого угла фигуры на поле.
  int ul_col;  ///< Столбец верхнего левого угла фигуры на поле.
} figure_t;

/**
 * @brief Перечисление состояний игры.
 */
typedef enum {
  Starting,  ///< Начальное состояние (запуск игры).
  Spawning,  ///< Появление новой фигуры.
  Falling,   ///< Обычное падение фигуры.
  MovingLeft,   ///< Перемещение фигуры влево.
  MovingRight,  ///< Перемещение фигуры вправо.
  MovingDown,   ///< Перемещение фигуры вниз.
  Dropping,     ///< Быстрое падение фигуры.
  Rotating,     ///< Вращение фигуры.
  Attaching,    ///< Фигура прикрепилась к полю.
  Paused,       ///< Игра на паузе.
  Continued,    ///< Игра продолжена.
  GameOver,     ///< Игра окончена.
} game_state_t;

/**
 * @struct handler_info_t
 * @brief Структура, содержащая всю информацию, необходимую для обработчиков
 * состояний игры.
 */
typedef struct {
  GameInfo_t *game_info;  ///< Указатель на GameInfo_t.
  figure_t *current_figure;  ///< Указатель на текущую фигуру.
  figure_t *next_figure;  ///< Указатель на следующую фигуру.
  game_state_t *game_state;  ///< Указатель на состояние игры.
  unsigned long long *previous_time;  ///< Указатель на предыдущее время.
  unsigned long long *current_time;  ///< Указатель на текущее время.
} handler_info_t;

/**
 * @enum direction_t
 * @brief Перечисление для указания направления движения.
 */
typedef enum { DirectionLeft, DirectionRight } direction_t;

// --- Вспомогательные функции для обработки состояний ---
void HandleStartingState(handler_info_t *info);
void HandleSpawningState(handler_info_t *info);
void HandleFallingState(handler_info_t *info);
void HandleMovingDownState(handler_info_t *info);
void HandleDroppingState(handler_info_t *info);
void HandleAttachingState(handler_info_t *info);
void HandleContinuedtate(handler_info_t *info);
void HandleMovingRotateState(handler_info_t *info);

// --- Функции для управления игрой ---
void StartGame(GameInfo_t *game_info, figure_t *figure, figure_t *next_figure);
void StopGame(GameInfo_t *game_info, figure_t *figure, figure_t *next_figure);

// --- Функции для управления памятью ---
int AllocateArray(int ***arr, int rows, int cols);
void FreeArray(int **array, int rows);
void FreeMemory(GameInfo_t *game_info, figure_t *figure, figure_t *next);

// --- Макросы и функции для копирования матриц ---
#define CopyMatrixToFigure(dest, src)           \
  _Generic((src),                               \
      const int(*)[4]: CopyMatrix2dToFigure,    \
      int(*)[4]: CopyMatrix2dToFigure,          \
      const int(*)[4][4]: CopyMatrix2dToFigure, \
      int(*)[4][4]: CopyMatrix2dToFigure,       \
      int **: CopyMatrixPtrToFigure)(dest, src)

int CopyMatrix2dToFigure(figure_t *dest_figure, const int src[4][4]);
int CopyMatrixPtrToFigure(figure_t *dest_figure, int **src);
int CopyMatrixToMatrix(int **dest, int **src);

// --- Функции для управления фигурами и полем ---
int createEmptyFigure(figure_t *figure);
int InitFigure(int figure_type, figure_t *result_figure);
int GenerateNextFigure(figure_t *figure);
int PositionFigure(int **v_field, figure_t *v_figure);
int SpawnFigure(GameInfo_t *game_info, figure_t *current_figure,
                figure_t *next_figure);
int Rotate(figure_t *figure);
int RotateInField(GameInfo_t *game_info, figure_t *figure);
int MoveHorizontal(direction_t direction, GameInfo_t *game_info,
                   figure_t *figure);
int MoveDown(GameInfo_t *game_info, figure_t *figure);
void Drop(GameInfo_t *game_info, figure_t *figure);
int DuplicateFigure(figure_t *dst, figure_t *src);
int CheckDataPointers(GameInfo_t *game_info, figure_t *figure);
int MakeVirtualData(GameInfo_t *game_info, figure_t *figure, int ***v_field,
                    figure_t *v_figure);
void FreeVirtualData(int **virtual_field, figure_t *figure);
void DeleteFigure(int **virtual_field, figure_t *figure);
void CopyField(int **dst, int **src, int rows, int cols);

// --- Функции для управления счетом и уровнем ---
int ReadHighScore();
void WriteHighScore(int high_score);
void UpdateHighScore(GameInfo_t *game_info);
int CountScore(int lines_number);
int GetSpeedFromLevel(int level);
int GetLevelFromScore(int score);

// --- Вспомогательные функции ---
void UpdateGameInfo(GameInfo_t *game_info);
unsigned long long GetTime();

#endif