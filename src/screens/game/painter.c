#include "screens/game/painter.h"
#include "app.h"
#include "colors.h"
#include "config.h"
#include "engine/painter.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <stdint.h>
#include <stdio.h>

int32_t lastLevel = -1;
int32_t lastLinesCleared = -1;
int32_t lastTotal = -1;

SDL_Texture *levelTexture = nullptr;
SDL_Texture *totalTexture = nullptr;
SDL_Texture *linesClearedTexture = nullptr;

static char levelText[20];
static char linesClearedText[20];
static char totalText[20];

static char levelFormat[] = "Level\n%d";
static char linesClearedFormat[] = "Cleared\n%d";
static char totalFormat[] = "Total\n%d";

void drawPlayfield(const Shape *player, const Square *opponent) {
  static const SDL_Point origin = {.x = SIDEBAR_WIDTH, .y = 0};
  static const SDL_FRect rect = {
    .x = (float)origin.x,
    .y = (float)origin.y,
    .w = (float)WAR_ZONE_WIDTH,
    .h = (float)CANVAS_HEIGHT,
  };

  drawGuide(&rect);
  drawShape(player, &origin);
  drawArrSquares(opponent, &origin);
}

void drawSidebar(const Shape *nextPlayer, const Score *score) {
  static const SDL_FRect backgroundRect = {
    .x = 0, .y = 0, .w = (float)SIDEBAR_WIDTH, .h = (float)CANVAS_HEIGHT
  };

  App_SetRenderDrawColor(App_renderer, UI_SIDEBAR_BACKGROUND);
  SDL_RenderFillRect(App_renderer, &backgroundRect);

  static const SDL_Point nextPlayerOrigin = {
    .x = SQUARE_WIDTH,
    .y = SQUARE_WIDTH,
  };

  static const SDL_FRect nextPlayerGuideRect = {
    .x = (float)nextPlayerOrigin.x,
    .y = (float)nextPlayerOrigin.y,
    .w = (float)(SQUARE_WIDTH * 4),
    .h = (float)(SQUARE_WIDTH * 2),
  };

  drawGuide(&nextPlayerGuideRect);
  drawShape(nextPlayer, &nextPlayerOrigin);

  if (score->level != lastLevel) {
    sprintf(levelText, levelFormat, score->level);
    SDL_DestroyTexture(levelTexture);
    makeFontTexture(levelText, smallFont, UI_WHITE_TEXT, &levelTexture);
    lastLevel = score->level;
  }
  if (score->linesCleared != lastLinesCleared) {
    sprintf(linesClearedText, linesClearedFormat, score->linesCleared);
    SDL_DestroyTexture(linesClearedTexture);
    makeFontTexture(
      linesClearedText, smallFont, UI_WHITE_TEXT, &linesClearedTexture
    );
    lastLinesCleared = score->linesCleared;
  }
  if (score->total != lastTotal) {
    sprintf(totalText, totalFormat, score->total);
    SDL_DestroyTexture(totalTexture);
    makeFontTexture(totalText, smallFont, UI_WHITE_TEXT, &totalTexture);
    lastTotal = score->total;
  }

  // clang-format off
  SDL_RenderTexture(
    App_renderer,
    levelTexture,
    nullptr,
    &(SDL_FRect){
      .w = (float)levelTexture->w,
      .h = (float)levelTexture->h,
      .x = (float)(SQUARE_WIDTH / 3.0),
      .y = (float)(SQUARE_WIDTH * 4)
    }
  );
  SDL_RenderTexture(
    App_renderer,
    linesClearedTexture,
    nullptr,
    &(SDL_FRect){
      .w = (float)linesClearedTexture->w,
      .h = (float)linesClearedTexture->h,
      .x = (float)(SQUARE_WIDTH / 3.0),
      .y = (float)(SQUARE_WIDTH * 6)
    }
  );
  SDL_RenderTexture(
    App_renderer,
    totalTexture,
    nullptr,
    &(SDL_FRect){
      .w = (float)totalTexture->w,
      .h = (float)totalTexture->h,
      .x = (float)(SQUARE_WIDTH / 3.0),
      .y = (float)(SQUARE_WIDTH * 8)
    }
  );
  // clang-format on
}

void cleanGameBrushes() {
  SDL_DestroyTexture(levelTexture);
  SDL_DestroyTexture(totalTexture);
  SDL_DestroyTexture(linesClearedTexture);
  lastLevel = -1;
  lastLinesCleared = -1;
  lastTotal = -1;
}
