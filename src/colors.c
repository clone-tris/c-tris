#include "colors.h"
#include <SDL3/SDL_pixels.h>

void App_SetRenderDrawColor(SDL_Renderer *renderer, uint32_t color) {
  SDL_Color c = App_Color(color);

  SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

SDL_Color App_Color(const uint32_t color) {
  const Uint8 r = (color >> 24) & 0xFF;
  const Uint8 g = (color >> 16) & 0xFF;
  const Uint8 b = (color >> 8) & 0xFF;
  const Uint8 a = color & 0xFF;

  return (SDL_Color){.r = r, .g = g, .b = b, .a = a};
}
