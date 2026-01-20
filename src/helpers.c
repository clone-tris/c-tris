#include "helpers.h"
#include <SDL3/SDL_stdinc.h>

int32_t randomInRange(Range range) {
  int rangeSize = range.end - range.start + 1;
  return range.start + (SDL_rand(3623 + SDL_rand(4979)) % rangeSize);
}

int32_t max(int32_t a, int32_t b) {
  if (a > b) {
    return a;
  }
  return b;
}

int32_t min(int32_t a, int32_t b) {
  if (a < b) {
    return a;
  }
  return b;
}
