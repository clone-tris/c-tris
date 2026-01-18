#include "menu_screen.h"
#include "app.h"
#include "config.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "engine/screen.h"
#include <stdio.h>

static void MenuScreen_draw(Screen *screen);
static void MenuScreen_cleanup(Screen *screen);
static const ScreenVTable MenuScreen_vtable;

typedef struct MenuScreen {
  Screen screen;
  int x;
  int y;
} MenuScreen;

Screen *MenuScreen_create(void) {
  MenuScreen *self = SDL_calloc(1, sizeof(*self));
  self->screen.vtable = &MenuScreen_vtable;
  self->x = 0;
  self->y = 0;
  return (Screen *)self;
}

static void MenuScreen_draw(Screen *screen) {
  MenuScreen *self = (MenuScreen *)screen;

  SDL_SetRenderDrawColor(App_renderer, 0, 0, 0, 255);
  SDL_RenderClear(App_renderer);

  SDL_SetRenderDrawColor(App_renderer, 69 * 3, 69 * 2, 69 * 3, 255);
  SDL_FRect rect = {
    (float)self->x * (float)SQUARE_WIDTH,
    (float)self->y * (float)SQUARE_WIDTH,
    (float)SQUARE_WIDTH * 4,
    (float)SQUARE_WIDTH * 3
  };
  SDL_RenderFillRect(App_renderer, &rect);
}

static void MenuScreen_keyDown(Screen *screen, SDL_Scancode scancode) {
  MenuScreen *self = (MenuScreen *)screen;
  switch (scancode) {
    case SDL_SCANCODE_D:
      self->x += 1;
      break;
    case SDL_SCANCODE_A:
      self->x -= 1;
      break;
    case SDL_SCANCODE_W:
      self->y -= 1;
      break;
    case SDL_SCANCODE_S:
      self->y += 1;
      break;
    default:
      break;
  }
}

static void MenuScreen_cleanup(Screen *screen) {
  MenuScreen *self = (MenuScreen *)screen;
  printf("Cleaning up MenuScreen\n");
  SDL_free(self);
}

static const ScreenVTable MenuScreen_vtable = {
  .draw = MenuScreen_draw,
  .update = nullptr,
  .keyDown = MenuScreen_keyDown,
  .mouseButtonUp = nullptr,
  .cleanup = MenuScreen_cleanup,
};
