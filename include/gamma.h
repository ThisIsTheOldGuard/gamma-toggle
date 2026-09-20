#ifndef GAMMA_H
#define GAMMA_H

#include <windows.h>

// Режимы работы
typedef enum {
    GAMMA_TOGGLE = 0,
    GAMMA_ENABLE = 1,
    GAMMA_DISABLE = 2
} GammaMode;

// Константы
#define RAMP_SIZE 256
#define RAMP_MAX 65535
#define GAMMA_VALUE_BRIGHT 0.45
#define GAMMA_VALUE_DEFAULT 1.0
#define GAMMA_THRESHOLD 35000 // Порог определения включенной гаммы

// Функции
void ShowMonitorList(void);
void SetMonitorGamma(GammaMode mode, int targetMonitorNumber);
int IsGammaEnabled(int targetMonitorNumber);

#endif // GAMMA_H