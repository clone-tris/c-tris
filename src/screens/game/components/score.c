#include "score.h"

Score Score_create() {
  return (Score){.level = 1, .total = 0, .linesCleared = 0};
}
