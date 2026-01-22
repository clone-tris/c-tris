#include "colors.h"
#include <SDL3/SDL_pixels.h>

void App_SetRenderDrawColor(SDL_Renderer *renderer, const uint32_t color) {
  const SDL_Color c = App_Color(color);

  SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

SDL_Color App_Color(const uint32_t color) {
  const Uint8 r = (color >> 24) & 0xFF;
  const Uint8 g = (color >> 16) & 0xFF;
  const Uint8 b = (color >> 8) & 0xFF;
  const Uint8 a = color & 0xFF;

  return (SDL_Color){.r = r, .g = g, .b = b, .a = a};
}

SDL_FColor App_FColor(const uint32_t color) {
  const Uint8 r = (color >> 24) & 0xFF;
  const Uint8 g = (color >> 16) & 0xFF;
  const Uint8 b = (color >> 8) & 0xFF;
  const Uint8 a = color & 0xFF;
  // clang-format off
  return (SDL_FColor){
    .r = (float)r / 255.0F,
    .g = (float)g / 255.0F,
    .b = (float)b / 255.0F,
    .a = (float)a / 255.0F
  };
  // clang-format on
}
