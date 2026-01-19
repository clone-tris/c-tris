#include "screens/game/painter.h"
#include "colors.h"
#include "config.h"
#include "engine/painter.h"
#include <SDL3/SDL_rect.h>

void drawPlayfield(Shape *player) {
  static const SDL_Point origin = {.x = SIDEBAR_WIDTH, .y = 0};
  static const SDL_FRect rect = {
    .x = (float)origin.x,
    .y = (float)origin.y,
    .w = (float)WAR_ZONE_WIDTH,
    .h = (float)CANVAS_HEIGHT
  };

  drawGuide(&rect);
  drawShape(player, &origin);
}

void drawSidebar() {
  static const SDL_FRect rect = {
    .x = 0, .y = 0, .w = (float)SIDEBAR_WIDTH, .h = (float)CANVAS_HEIGHT
  };

  App_SetRenderDrawColor(App_renderer, UI_SIDEBAR_BACKGROUND);
  SDL_RenderFillRect(App_renderer, &rect);
}
