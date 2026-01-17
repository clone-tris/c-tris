#pragma once

#include <stdint.h>

typedef struct Range {
  int32_t start;
  int32_t end;
} Range;

int32_t randomInRange(Range);
