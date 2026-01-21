#include "app.h"
#include "colors.h"
#include "config.h"
#include "stb_ds.h"
#include "screens/game/components/shape.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <assert.h>
#include <stdint.h>

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

void drawSquares(const Square *squares, const SDL_Point *ref) {
  int32_t len = arrlen(squares);
  for (int i = 0; i < len; i++) {
    const Square square = squares[i];
    App_SetRenderDrawColor(App_renderer, square.color);

    const int x = ref->x + (square.column * SQUARE_WIDTH);
    const int y = ref->y + (square.row * SQUARE_WIDTH);

    SDL_RenderFillRect(
      App_renderer,
      &(SDL_FRect){
        .w = (float)SQUARE_WIDTH,
        .h = (float)SQUARE_WIDTH,
        .x = (float)x,
        .y = (float)y,
      }
    );
  }
}

void drawShape(const Shape *shape, const SDL_Point *ref) {
  // clang-format off
  drawSquares(
    shape->squares,
    &(SDL_Point){
      .x = ref->x + (shape->column * SQUARE_WIDTH),
      .y = ref->y + (shape->row * SQUARE_WIDTH),
    }
  );
  // clang-format on
}

bool makeFontTexture(char *text, SDL_Texture **texture) {
  SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(
    smallFont, text, 0, App_Color(UI_WHITE_TEXT), 0
  );
  if (!surface) {
    SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    return false;
  }

  *texture = SDL_CreateTextureFromSurface(App_renderer, surface);
  SDL_DestroySurface(surface);

  if (!*texture) {
    SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    return false;
  }

  return true;
}
