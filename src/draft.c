#include <stdio.h>
#include <stdlib.h>

typedef struct Screen Screen;

typedef struct ScreenVTable {
  void (*draw)(Screen *);
  void (*cleanup)(Screen *);
} ScreenVTable;

struct Screen {
  const ScreenVTable *vtable;
};

static const ScreenVTable MenuScreen_vtable;

typedef struct MenuScreen {
  Screen screen;
  char *title;
} MenuScreen;

Screen *MenuScreen_create(void) {
  MenuScreen *self = calloc(1, sizeof(*self));
  self->screen.vtable = &MenuScreen_vtable;
  self->title = "Main Menu";
  return (Screen *)self;
}

static void MenuScreen_draw(Screen *screen) {
  MenuScreen *self = (MenuScreen *)screen;
  printf("MenuScreen: %s\n", self->title);
}

static void MenuScreen_cleanup(Screen *screen) {
  MenuScreen *self = (MenuScreen *)screen;
  printf("Cleaning up MenuScreen\n");
  free(self);
}

static const ScreenVTable MenuScreen_vtable = {
  .draw = MenuScreen_draw,
  .cleanup = MenuScreen_cleanup,
};

static const ScreenVTable GameScreen_vtable;

typedef struct GameScreen {
  Screen screen;
  int score;
} GameScreen;

Screen *GameScreen_create(void) {
  GameScreen *self = calloc(1, sizeof(*self));
  self->screen.vtable = &GameScreen_vtable;
  self->score = 42;
  return (Screen *)self;
}

static void GameScreen_draw(Screen *screen) {
  GameScreen *game = (GameScreen *)screen;
  printf("GameScreen: Score = %d\n", game->score);
}

static void GameScreen_cleanup(Screen *screen) {
  GameScreen *self = (GameScreen *)screen;
  printf("Cleaning up GameScreen\n");
  free(self);
}

static const ScreenVTable GameScreen_vtable = {
  .draw = GameScreen_draw,
  .cleanup = GameScreen_cleanup,
};

int main(void) {
  Screen *screen;

  screen = MenuScreen_create();
  screen->vtable->draw(screen);
  screen->vtable->cleanup(screen);

  screen = GameScreen_create();
  screen->vtable->draw(screen);
  screen->vtable->cleanup(screen);

  return 0;
}
