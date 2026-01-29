#pragma once

#include "app.h"
#include <SDL3/SDL_render.h>
#include <stdint.h>

typedef struct Button {
  int32_t x;
  int32_t y;
  SDL_Texture *texture;
} Button;

Button Button_create(const char *, Cell);

bool Button_clicked(Button *, SDL_FPoint);
