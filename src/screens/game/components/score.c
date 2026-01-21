#include "score.h"

const int32_t POINTS[] = {0, 40, 100, 300, 1200};

Score Score_create() {
  return (Score){.level = 1, .total = 0, .linesCleared = 0};
}
