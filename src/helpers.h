#pragma once

#include <stdint.h>

typedef struct Range {
  int32_t start;
  int32_t end;
} Range;

int32_t randomInRange(Range);
int32_t max(int32_t a, int32_t b);
int32_t min(int32_t a, int32_t b);
