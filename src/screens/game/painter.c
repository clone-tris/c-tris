#include "screens/game/painter.h"
#include "config.h"
#include "engine/painter.h"
#include <SDL3/SDL_rect.h>

static const SDL_Point PLAYFIELD_REF = {.x = SIDEBAR_WIDTH, .y = 0};

static const SDL_FRect PLAYFIELD_RECT = {
  (float)PLAYFIELD_REF.x,
  (float)PLAYFIELD_REF.y,
  (float)WAR_ZONE_WIDTH,
  (float)CANVAS_HEIGHT
};

void drawPlayfield(Shape *player) {
  drawGuide(&PLAYFIELD_RECT);
  drawShape(player, &PLAYFIELD_REF);
}

void drawSidebar() {}
