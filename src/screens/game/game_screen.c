#include "game_screen.h"
#include "config.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "engine/app.h"
#include "engine/screen.h"
#include <stdio.h>

struct GameScreen {
  struct Screen screen;
};

static void GameScreen_draw(struct Screen *self) {
  (void)self;

  SDL_SetRenderDrawColor(App_renderer, 0, 0, 0, 255);
  SDL_RenderClear(App_renderer);

  SDL_SetRenderDrawColor(App_renderer, 69 * 1, 69 * 3, 69 * 1, 255);
  SDL_FRect rect = {
    (float)5 * (float)SQUARE_WIDTH,
    (float)6 * (float)SQUARE_WIDTH,
    (float)SQUARE_WIDTH * 3,
    (float)SQUARE_WIDTH * 2
  };
  SDL_RenderFillRect(App_renderer, &rect);
}

static void GameScreen_cleanup(struct Screen *self) {
  struct GameScreen *game = (struct GameScreen *)self;
  printf("Cleaning up GameScreen\n");
  SDL_free(game);
}

static const struct ScreenVTable GameScreen_vtable = {
  .draw = GameScreen_draw,
  .update = nullptr,
  .keyDown = nullptr,
  .mouse_button_up = nullptr,
  .cleanup = GameScreen_cleanup,
};

struct Screen *GameScreen_create(void) {
  struct GameScreen *game = SDL_calloc(1, sizeof(struct GameScreen));
  game->screen.vtable = &GameScreen_vtable;
  return (struct Screen *)game;
}
