#include <SDL3/SDL_stdinc.h>
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

void Screen_draw(Screen *screen) {
  if (screen->vtable->draw) {
    screen->vtable->draw(screen);
  }
}

void Screen_destroy(Screen **screen) {
  if (!screen || !*screen) {
    return;
  }

  if ((*screen)->vtable && (*screen)->vtable->cleanup) {
    (*screen)->vtable->cleanup(*screen);
  }

  SDL_free(*screen);
  *screen = nullptr;
}

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
  printf("Cleaning up MenuScreen\n");
  (void)screen;
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
  printf("Cleaning up GameScreen\n");
  (void)screen;
}

static const ScreenVTable GameScreen_vtable = {
  .draw = GameScreen_draw,
  .cleanup = GameScreen_cleanup,
};

int main(void) {
  Screen *screen;
  // simulation of polymorphism
  screen = MenuScreen_create();
  Screen_draw(screen);
  Screen_destroy(&screen);

  screen = GameScreen_create();
  Screen_draw(screen);
  Screen_destroy(&screen);

  return 0;
}
