#include "app.h"
#include "colors.h"
#include "config.h"
#include "stb_ds.h"
#include "engine/button.h"
#include "engine/popup.h"
#include "screens/game/components/shape.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <math.h>
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

typedef struct SquareAtPoint {
  SDL_FPoint position;
  TetrominoColor color;
} SquareAtPoint;

static constexpr float SW = SQUARE_WIDTH;
static constexpr float BW = SQUARE_BORDER_WIDTH;
static constexpr float IW = SW - (BW * 2);

void drawSquareAtPoint(SquareAtPoint square) {
  const float_t x = square.position.x;
  const float_t y = square.position.y;

  // Background
  App_SetRenderDrawColor(App_renderer, square.color);
  SDL_RenderFillRect(
    App_renderer,
    &(SDL_FRect){
      .w = (float)SW,
      .h = (float)SW,
      .x = x,
      .y = y,
    }
  );

  // Left Border

  // clang-format off
  const SDL_FColor sideBorder = App_FColor(SQUARE_BORDER_SIDE);
  SDL_RenderGeometry(
     App_renderer, nullptr,
     (SDL_Vertex[]) {
      {.color = sideBorder, .position = {.x = x, .y = y}},
      {.color = sideBorder, .position = {.x = x + BW, .y = y + BW}},
      {.color = sideBorder, .position = {.x = x, .y = y + BW}},
    },
    3, nullptr, 3);
  // clang-format on

  App_SetRenderDrawColor(App_renderer, SQUARE_BORDER_SIDE);
  SDL_RenderFillRect(
    App_renderer, &(SDL_FRect){.x = x, .y = y + BW, .w = BW, .h = IW}
  );

  // clang-format off
  SDL_RenderGeometry(
     App_renderer, nullptr,
     (SDL_Vertex[]) {
      {.color = sideBorder, .position = {.x = x, .y = y + BW + IW}},
      {.color = sideBorder, .position = {.x = x + BW, .y = y + BW + IW}},
      {.color = sideBorder, .position = {.x = x, .y = y + SW}},
    },
    3, nullptr, 3);
  // clang-format on

  // Top Border

  // clang-format off
  const SDL_FColor topBorder = App_FColor(SQUARE_BORDER_TOP);
  SDL_RenderGeometry(
     App_renderer, nullptr,
     (SDL_Vertex[]) {
      {.color = topBorder, .position = {.x = x, .y = y}},
      {.color = topBorder, .position = {.x = x + BW, .y = y }},
      {.color = topBorder, .position = {.x = x + BW, .y = y + BW}},
    },
    3, nullptr, 3);
  // clang-format on

  App_SetRenderDrawColor(App_renderer, SQUARE_BORDER_TOP);
  SDL_RenderFillRect(
    App_renderer, &(SDL_FRect){.x = x + BW, .y = y, .w = IW, .h = BW}
  );

  // clang-format off
  SDL_RenderGeometry(
     App_renderer, nullptr,
     (SDL_Vertex[]) {
      {.color = topBorder, .position = {.x = x + BW + IW, .y = y}},
      {.color = topBorder, .position = {.x = x + SW, .y = y }},
      {.color = topBorder, .position = {.x = x + BW + IW, .y = y + BW}},
    },
    3, nullptr, 3);
  // clang-format on

  // Right Border

  // clang-format off
  SDL_RenderGeometry(
     App_renderer, nullptr,
     (SDL_Vertex[]) {
      {.color = sideBorder, .position = {.x = x + SW, .y = y}},
      {.color = sideBorder, .position = {.x = x + SW, .y = y + BW}},
      {.color = sideBorder, .position = {.x = x + IW + BW, .y = y + BW}},
    },
    3, nullptr, 3);
  // clang-format on

  App_SetRenderDrawColor(App_renderer, SQUARE_BORDER_SIDE);
  SDL_RenderFillRect(
    App_renderer, &(SDL_FRect){.x = x + BW + IW, .y = y + BW, .w = BW, .h = IW}
  );

  // clang-format off
  SDL_RenderGeometry(
     App_renderer, nullptr,
     (SDL_Vertex[]) {
      {.color = sideBorder, .position = {.x = x + BW + IW, .y = y + BW + IW}},
      {.color = sideBorder, .position = {.x = x + SW, .y = y + BW + IW}},
      {.color = sideBorder, .position = {.x = x + SW, .y = y + SW}},
    },
    3, nullptr, 3);
  // clang-format on

  // Bottom Border

  const SDL_FColor bottomBorder = App_FColor(SQUARE_BORDER_BOTTOM);
  // clang-format off
  SDL_RenderGeometry(
     App_renderer, nullptr,
     (SDL_Vertex[]) {
      {.color = bottomBorder, .position = {.x = x + BW + IW, .y = y + BW + IW}},
      {.color = bottomBorder, .position = {.x = x + SW, .y = y + SW}},
      {.color = bottomBorder, .position = {.x = x + IW + BW, .y = y + SW}},
    },
    3, nullptr, 3);
  // clang-format on

  App_SetRenderDrawColor(App_renderer, SQUARE_BORDER_BOTTOM);
  SDL_RenderFillRect(
    App_renderer, &(SDL_FRect){.x = x + BW, .y = y + IW + BW, .w = IW, .h = BW}
  );

  // clang-format off
  SDL_RenderGeometry(
     App_renderer, nullptr,
     (SDL_Vertex[]) {
      {.color = bottomBorder, .position = {.x = x, .y = y + SW}},
      {.color = bottomBorder, .position = {.x = x + BW, .y = y + BW + IW}},
      {.color = bottomBorder, .position = {.x = x + BW, .y = y + SW}},
    },
    3, nullptr, 3);
  // clang-format on
}

void drawNSquares(const Square *squares, const SDL_Point *ref, int32_t n) {
  for (int i = 0; i < n; i++) {
    const Square square = squares[i];
    // clang-format off
    drawSquareAtPoint(
      (SquareAtPoint){
      .position = (SDL_FPoint){
         .x = (float)(ref->x + (square.column * SQUARE_WIDTH)),
         .y = (float)(ref->y + (square.row * SQUARE_WIDTH)),
       },
      .color = square.color
      }
    );
    // clang-format on
  }
}

void drawArrSquares(const Square *squares, const SDL_Point *ref) {
  drawNSquares(squares, ref, arrlen(squares));
}

void drawShape(const Shape *shape, const SDL_Point *ref) {
  // clang-format off
  drawArrSquares(
    shape->squares,
    &(SDL_Point){
      .x = ref->x + (shape->column * SQUARE_WIDTH),
      .y = ref->y + (shape->row * SQUARE_WIDTH),
    }
  );
  // clang-format on
}

void drawButton(Button *button) {
  SDL_RenderTexture(
    App_renderer,
    button->texture,
    nullptr,
    &(SDL_FRect){
      .x = (float)button->x,
      .y = (float)button->y,
      .w = (float)button->texture->w,
      .h = (float)button->texture->h,
    }
  );
}

void drawPopup(const Popup *popup) {
  SDL_RenderTexture(
    App_renderer,
    popup->texture,
    nullptr,
    &(SDL_FRect){
      .x = (float)(CANVAS_WIDTH - popup->texture->w) / 2,
      .y = (float)(CANVAS_HEIGHT - popup->texture->h) / 2,
      .w = (float)popup->texture->w,
      .h = (float)popup->texture->h,
    }
  );
}

bool makeFontTexture(
  const char *text, TTF_Font *font, const uint32_t color, SDL_Texture **texture
) {
  SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(
    font, text, 0, App_Color(color), 0
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
