#include "colors.h"

void App_SetRenderDrawColor(SDL_Renderer *renderer, Uint32 color) {
  Uint8 r = (color >> 24) & 0xFF;
  Uint8 g = (color >> 16) & 0xFF;
  Uint8 b = (color >> 8) & 0xFF;
  Uint8 a = color & 0xFF;

  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
