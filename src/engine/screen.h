#pragma once

#include "app.h"

struct Screen;

struct ScreenVTable {
  void (*draw)(struct Screen *self, AppState* as);
  void (*cleanup)(struct Screen *self, AppState* as);
};

struct Screen {
  const struct ScreenVTable *vtable;
};

