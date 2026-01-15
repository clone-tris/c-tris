#pragma once

struct Screen;

struct ScreenVTable {
  void (*draw)(struct Screen *self);
  void (*cleanup)(struct Screen *self);
};

struct Screen {
  const struct ScreenVTable *vtable;
};

