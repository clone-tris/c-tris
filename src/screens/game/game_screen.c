#include "game_screen.h"
#include <stdio.h>
#include <stdlib.h>

struct GameScreen {
  struct Screen screen;
  int score;
};

static void GameScreen_draw(struct Screen *self, AppState *as) {
  (void)as;
  struct GameScreen *game = (struct GameScreen *)self;
  printf("GameScreen: Score = %d\n", game->score);
}

static void GameScreen_cleanup(struct Screen *self, AppState *as) {
  (void)as;
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
