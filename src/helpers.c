#include "helpers.h"
#include "SDL3/SDL_stdinc.h"
#include <stdlib.h>

int32_t randomInRange(Range range) {
  int rangeSize = range.end - range.start + 1;
  return range.start + (SDL_rand(3623 + SDL_rand(4979)) % rangeSize);
}
