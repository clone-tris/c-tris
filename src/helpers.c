#include "helpers.h"
#include <stdlib.h>

int32_t randomInRange(Range range) {
  return range.start +
    (rand() / (RAND_MAX / (range.end - range.start + 1) + 1));
}
