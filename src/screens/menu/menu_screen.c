#include "menu_screen.h"
#include <stdio.h>
#include <stdlib.h>

struct MenuScreen {
  struct Screen screen;
  char *title;
};

static void MenuScreen_draw(struct Screen *self, AppState *as) {
  (void)as;
  struct MenuScreen *menu = (struct MenuScreen *)self;
  printf("MenuScreen: %s\n", menu->title);
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
