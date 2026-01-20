#pragma once

#include "screens/game/components/score.h"
#include "screens/game/components/shape.h"

extern SDL_Texture *levelTexture;
extern SDL_Texture *totalTexture;
extern SDL_Texture *linesClearedTexture;

void drawPlayfield(Shape *);
void drawSidebar(Shape *, Score *);
