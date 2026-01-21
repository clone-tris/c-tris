#pragma once

#include <stdint.h>

typedef struct Score {
  int32_t level;
  int32_t total;
  int32_t linesCleared;
} Score;

extern const int32_t POINTS[];

Score Score_create();
