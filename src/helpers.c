#include "helpers.h"
#include <SDL3/SDL_stdinc.h>

int32_t randomInRange(const Range range) {
  const int rangeSize = range.end - range.start + 1;
  return range.start + (SDL_rand(3623 + SDL_rand(4979)) % rangeSize);
}

int32_t max(const int32_t a, const int32_t b) {
  if (a > b) {
    return a;
  }
  return b;
}

int32_t min(const int32_t a, const int32_t b) {
  if (a < b) {
    return a;
  }
  return b;
}
