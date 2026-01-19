#include "screens/game/painter.h"
#include "colors.h"
#include "config.h"
#include "engine/painter.h"
#include <SDL3/SDL_rect.h>

static const SDL_FRect SIDEBAR_RECT = {
  .x = 0, .y = 0, .w = (float)SIDEBAR_WIDTH, .h = (float)CANVAS_HEIGHT
};

static const SDL_Point PLAYFIELD_REF = {.x = SIDEBAR_WIDTH, .y = 0};
static const SDL_FRect PLAYFIELD_RECT = {
  .x = (float)PLAYFIELD_REF.x,
  .y = (float)PLAYFIELD_REF.y,
  .w = (float)WAR_ZONE_WIDTH,
  .h = (float)CANVAS_HEIGHT
};

void drawPlayfield(Shape *player) {
  drawGuide(&PLAYFIELD_RECT);
  drawShape(player, &PLAYFIELD_REF);
}

void drawSidebar() {
  App_SetRenderDrawColor(App_renderer, UI_SIDEBAR_BACKGROUND);
  SDL_RenderFillRect(App_renderer, &SIDEBAR_RECT);
}
