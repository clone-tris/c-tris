#pragma once

#include "SDL3/SDL_scancode.h"
struct Screen;

struct ScreenVTable {
  void (*draw)(struct Screen *);
  void (*update)(struct Screen *);
  void (*key_down)(struct Screen *, SDL_Scancode);
  void (*mouse_button_up)(struct Screen *);
  void (*cleanup)(struct Screen *);
};

struct Screen {
  const struct ScreenVTable *vtable;
};
