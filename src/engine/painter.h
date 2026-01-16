#pragma once

#include "SDL3/SDL_rect.h"
#include "screens/game/components/shape.h"
#include "screens/game/components/square.h"

void drawGuide(const SDL_FRect *);
void drawShape(const Shape *, const SDL_Point *);
void drawSquares(const Square *, int, const SDL_Point *);
