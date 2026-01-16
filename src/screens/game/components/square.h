#pragma once

#include "colors.h"
#include <stdint.h>

typedef struct Square {
  int32_t row;
  int32_t column;
  TetrominoColor color;
} Square;
