#include "engine/button.h"
#include "app.h"
#include "colors.h"
#include "config.h"
#include "engine/painter.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <math.h>
#include <stdint.h>

Button Button_create(const char *text, Cell cell) {
  SDL_Texture *textTexture = nullptr;
  makeFontTexture(text, smallFont, UI_BUTTON_TEXT, &textTexture);

  int32_t textWidth = textTexture->w;
  int32_t textHeight = textTexture->h;
  int32_t height = SQUARE_WIDTH;

  int32_t rawWidth = textWidth + (BUTTON_PADDING_LEFT * 2);
  int32_t width = (int32_t)ceil(rawWidth / (double)SQUARE_WIDTH) * SQUARE_WIDTH;

  int32_t paddingTop = (height - textHeight) / 2;
  int32_t paddingLeft = (width - textWidth) / 2;

  SDL_Texture *buttonTexture = SDL_CreateTexture(
    App_renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_TARGET,
    width,
    height
  );

  SDL_SetRenderTarget(App_renderer, buttonTexture);
  App_SetRenderDrawColor(App_renderer, UI_BUTTON_BACKGROUND);
  SDL_RenderClear(App_renderer);
  // clang-format off
  SDL_RenderTexture(
    App_renderer,
    textTexture,
    nullptr,
    &(SDL_FRect){
      .x = (float)paddingLeft,
      .y = (float)paddingTop,
      .w = (float)textWidth,
      .h = (float)textHeight
    }
  );
  // clang-format on
  SDL_SetRenderTarget(App_renderer, nullptr);
  SDL_DestroyTexture(textTexture);

  // clang-format off
  return (Button) {
    .x = cell.column * SQUARE_WIDTH,
    .y = cell.row * SQUARE_WIDTH,
    .texture = buttonTexture
  };
  // clang-format on
}

bool Button_clicked(Button *self, SDL_FPoint mouse) {
  // clang-format off
  return (
    (float)self->x <= mouse.x
    && (mouse.x <= (float)self->x + (float)self->texture->w)
    && (float)self->y <= mouse.y
    && (mouse.y <= (float)self->y + (float)self->texture->h)
  );
  // clang-format on
}
