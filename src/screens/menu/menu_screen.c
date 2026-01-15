#include "menu_screen.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

struct MenuScreen {
  struct Screen screen;
  char *title;
};

static void MenuScreen_draw(struct Screen *self, AppState *as) {
  (void)as;
  (void)self;

  SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, 255);
  SDL_RenderClear(as->renderer);

  SDL_SetRenderDrawColor(as->renderer, 69 * 3, 69 * 2, 69 * 3, 255);
  SDL_FRect rect = {
    (float)2 * (float)SQUARE_WIDTH,
    (float)2 * (float)SQUARE_WIDTH,
    (float)SQUARE_WIDTH * 4,
    (float)SQUARE_WIDTH * 3
  };
  SDL_RenderFillRect(as->renderer, &rect);

  SDL_RenderPresent(as->renderer);
}

static void MenuScreen_cleanup(struct Screen *self, AppState *as) {
  (void)as;
  struct MenuScreen *menu = (struct MenuScreen *)self;
  printf("Cleaning up MenuScreen\n");
  free(menu);
}

static const struct ScreenVTable MenuScreen_vtable = {
  .draw = MenuScreen_draw,
  .cleanup = MenuScreen_cleanup,
};

struct Screen *MenuScreen_create(void) {
  struct MenuScreen *menu = malloc(sizeof(struct MenuScreen));
  menu->screen.vtable = &MenuScreen_vtable;
  menu->title = "Main Menu";
  return (struct Screen *)menu;
}
