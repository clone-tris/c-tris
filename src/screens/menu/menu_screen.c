#include "menu_screen.h"
#include "config.h"
#include "engine/painter.h"
#include "engine/screen.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <stdio.h>

static void MenuScreen_draw(Screen *screen);
static void MenuScreen_cleanup(Screen *screen);
static const ScreenVTable MenuScreen_vtable;

typedef struct MenuScreen {
  Screen screen;
} MenuScreen;

bool MenuScreen_create(Screen **screen) {
  MenuScreen *self = SDL_calloc(1, sizeof(*self));
  if (!self) {
    self = nullptr;
    return false;
  }

  //
  self->screen.vtable = &MenuScreen_vtable;
  *screen = (Screen *)self;
  return true;
}

static void MenuScreen_draw(Screen *screen) {
  MenuScreen *self = (MenuScreen *)screen;
  static const SDL_FRect rect = {
    .x = 0,
    .y = 0,
    .w = CANVAS_HEIGHT,
    .h = CANVAS_HEIGHT,
  };
  drawGuide(&rect);
  drawNSquares(graphic, &(SDL_Point){.x = 0, .y = 0}, 52);
}

static void MenuScreen_keyDown(Screen *screen, SDL_Scancode scancode) {
  MenuScreen *self = (MenuScreen *)screen;
  switch (scancode) {
    default:
      break;
  }
}

static void MenuScreen_cleanup(Screen *screen) {
  printf("Cleaning up MenuScreen\n");
  (void)screen;
}

static const ScreenVTable MenuScreen_vtable = {
  .draw = MenuScreen_draw,
  .update = nullptr,
  .keyDown = MenuScreen_keyDown,
  .mouseButtonUp = nullptr,
  .cleanup = MenuScreen_cleanup,
};
