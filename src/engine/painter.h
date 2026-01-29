#pragma once

#include "SDL3/SDL_rect.h"
#include "engine/button.h"
#include "engine/popup.h"
#include "screens/game/components/shape.h"
#include "screens/game/components/square.h"
#include <stdint.h>

void drawGuide(const SDL_FRect *);
void drawShape(const Shape *, const SDL_Point *);
void drawArrSquares(const Square *, const SDL_Point *);
void drawNSquares(const Square *, const SDL_Point *, int32_t);
void drawButton(Button *button);
void drawPopup(const Popup *popup);
bool makeFontTexture(const char *, TTF_Font *, uint32_t, SDL_Texture **);
