#pragma once

#include <stdint.h>

typedef struct Score {
  int32_t level;
  int32_t total;
  int32_t linesCleared;
} Score;

static const int32_t POINTS[] = {0, 40, 100, 300, 1200};

Score Score_create();
