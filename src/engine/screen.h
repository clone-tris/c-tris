#pragma once

#include "SDL3/SDL_scancode.h"
struct Screen;

typedef struct ScreenVTable {
  void (*draw)(struct Screen *);
  void (*update)(struct Screen *);
  void (*keyDown)(struct Screen *, SDL_Scancode);
  void (*mouse_button_up)(struct Screen *);
  void (*cleanup)(struct Screen *);
} ScreenVTable;

typedef struct Screen {
  const ScreenVTable *vtable;
} Screen;
