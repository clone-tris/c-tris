#include "menu_screen.h"
#include "config.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "engine/app.h"
#include "engine/screen.h"
#include <stdio.h>

struct MenuScreen {
  struct Screen screen;
  int x;
  int y;
};

static void MenuScreen_draw(struct Screen *screen) {
  struct MenuScreen *self = (struct MenuScreen *)screen;

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

static void key_down(struct Screen *screen, SDL_Scancode scancode) {
  struct MenuScreen *self = (struct MenuScreen *)screen;
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

static void MenuScreen_cleanup(struct Screen *screen) {
  struct MenuScreen *self = (struct MenuScreen *)screen;
  printf("Cleaning up MenuScreen\n");
  SDL_free(self);
}

static const struct ScreenVTable MenuScreen_vtable = {
  .draw = MenuScreen_draw,
  .update = nullptr,
  .key_down = key_down,
  .mouse_button_up = nullptr,
  .cleanup = MenuScreen_cleanup,
};

struct Screen *MenuScreen_create(void) {
  struct MenuScreen *self = SDL_calloc(1, sizeof(struct MenuScreen));
  self->screen.vtable = &MenuScreen_vtable;
  self->x = 0;
  self->y = 0;
  return (struct Screen *)self;
}
