#pragma once

#include "screens/game/components/score.h"
#include "screens/game/components/shape.h"

void drawPlayfield(const Shape *);
void drawSidebar(const Shape *, const Score *);
void cleanGameBrushes();
