#include "app.h"
#include "colors.h"
#include "config.h"
#include "SDL3/SDL_rect.h"

void drawGuide(const SDL_FRect *rect) {
  App_SetRenderDrawColor(App_renderer, UI_BACKGROUND);
  SDL_RenderFillRect(App_renderer, rect);

  App_SetRenderDrawColor(App_renderer, UI_GUIDE);

  const int rows = (int)(rect->h / (float)SQUARE_WIDTH);
  const int columns = (int)(rect->w / (float)SQUARE_WIDTH);

  for (int i = 0; i < rows + 1; i++) {
    const auto lineY = rect->y + (float)(i * SQUARE_WIDTH);
    SDL_RenderLine(App_renderer, rect->x, lineY, rect->x + rect->w, lineY);
  }

  for (int i = 0; i < columns + 1; i++) {
    const auto lineX = rect->x + (float)(i * SQUARE_WIDTH);
    SDL_RenderLine(App_renderer, lineX, rect->y, lineX, rect->y + rect->h);
  }
}
