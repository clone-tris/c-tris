#include "engine/popup.h"
#include "app.h"
#include "colors.h"
#include "config.h"
#include "engine/painter.h"
#include <SDL3/SDL_render.h>

Popup Popup_create(const char *text) {
  SDL_Texture *textTexture = nullptr;
  makeFontTexture(text, largeFont, UI_POPUP_TEXT, &textTexture);
  int32_t textWidth = textTexture->w;
  int32_t textHeight = textTexture->h;
  int32_t width = SQUARE_WIDTH * 10;
  int32_t height = SQUARE_WIDTH * 4;

  SDL_Texture *popupTexture = SDL_CreateTexture(
    App_renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_TARGET,
    width,
    height
  );
  SDL_SetRenderTarget(App_renderer, popupTexture);
  App_SetRenderDrawColor(App_renderer, UI_POPUP_BACKGROUND);

  int32_t paddingLeft = (width - textWidth) / 2;
  int32_t paddingTop = (height - textHeight) / 2;

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
    .h = (float)textHeight}
  );
  // clang-format on

  SDL_DestroyTexture(textTexture);
  return (Popup){.texture = popupTexture};
}

void Popup_draw(const Popup *self) {
  SDL_RenderTexture(
    App_renderer,
    self->texture,
    nullptr,
    &(SDL_FRect){
      .x = (float)(CANVAS_WIDTH - self->texture->w) / 2,
      .y = (float)(CANVAS_HEIGHT - self->texture->h) / 2,
      .w = (float)self->texture->w,
      .h = (float)self->texture->h,
    }
  );
}
