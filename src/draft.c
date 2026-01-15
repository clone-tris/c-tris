#include <stdio.h>
#include <stdlib.h>

struct Screen;

struct ScreenVTable {
  void (*draw)(struct Screen *self);
  void (*cleanup)(struct Screen *self);
};

struct Screen {
  const struct ScreenVTable *vtable;
};

struct MenuScreen {
  struct Screen screen;
  char *title;
};

struct GameScreen {
  struct Screen screen;
  int score;
};

static void MenuScreen_draw(struct Screen *self) {
  struct MenuScreen *menu = (struct MenuScreen *)self;
  printf("MenuScreen: %s\n", menu->title);
}

static void MenuScreen_cleanup(struct Screen *self) {
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

static void GameScreen_draw(struct Screen *self) {
  struct GameScreen *game = (struct GameScreen *)self;
  printf("GameScreen: Score = %d\n", game->score);
}

static void GameScreen_cleanup(struct Screen *self) {
  struct GameScreen *game = (struct GameScreen *)self;
  printf("Cleaning up GameScreen\n");
  free(game);
}

static const struct ScreenVTable GameScreen_vtable = {
  .draw = GameScreen_draw,
  .cleanup = GameScreen_cleanup,
};

struct Screen *GameScreen_create(void) {
  struct GameScreen *game = malloc(sizeof(struct GameScreen));
  game->screen.vtable = &GameScreen_vtable;
  game->score = 42;
  return (struct Screen *)game;
}

int main(void) {
  struct Screen *screen;

  screen = MenuScreen_create();
  screen->vtable->draw(screen);
  screen->vtable->cleanup(screen);

  screen = GameScreen_create();
  screen->vtable->draw(screen);
  screen->vtable->cleanup(screen);

  return 0;
}
