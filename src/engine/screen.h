#pragma once

#include "SDL3/SDL_scancode.h"

typedef struct Screen Screen;

typedef struct ScreenVTable {
  void (*draw)(Screen *);
  void (*update)(Screen *);
  void (*keyDown)(Screen *, SDL_Scancode);
  void (*mouseButtonUp)(Screen *);
  void (*destroy)(Screen *);
} ScreenVTable;

typedef struct Screen {
  const ScreenVTable *vtable;
} Screen;

void Screen_draw(Screen *);
void Screen_update(Screen *);
void Screen_keyDown(Screen *, SDL_Scancode);
void Screen_mouseButtonUp(Screen *);
void Screen_destroy(Screen *);
