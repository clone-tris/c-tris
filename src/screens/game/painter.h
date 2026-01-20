#pragma once

#include "screens/game/components/score.h"
#include "screens/game/components/shape.h"

void drawPlayfield(Shape *);
void drawSidebar(Shape *, Score *);
void cleanGameBrushes();
