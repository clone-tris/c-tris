#pragma once

#include <SDL3/SDL_render.h>

typedef struct Popup {
  SDL_Texture *texture;
} Popup;

Popup Popup_create(const char *);
void Popup_draw(const Popup *);
