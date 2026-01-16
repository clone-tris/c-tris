#pragma once

#include "SDL3/SDL_scancode.h"
typedef struct Screen Screen;

typedef struct ScreenVTable {
  void (*draw)(Screen *);
  void (*update)(Screen *);
  void (*keyDown)(Screen *, SDL_Scancode);
  void (*mouse_button_up)(Screen *);
  void (*cleanup)(Screen *);
} ScreenVTable;

struct Screen {
  const ScreenVTable *vtable;
};
